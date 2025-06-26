#!/usr/bin/env python3
"""
CA65 Listing to C++ Translator
"""

import sys
import os
from pathlib import Path

TAB = "    "

class ListingTranslator:
    def __init__(self, listing_file: str, config_dir: str = None):
        self.listing_file = listing_file
        self.lines = []
        self.return_label_index = 0
        self.source_output = ""
        
        self._parse_listing()
        self._generate_code()
    
    def _parse_listing(self):
        with open(self.listing_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line = line.rstrip()
                if not line or line.startswith('ca65') or line.startswith('Main') or line.startswith('Current') or line.startswith('------'):
                    continue
                
                if len(line) >= 7 and line[:7].strip().endswith('r'):
                    rest = line[7:].strip()
                    if rest:
                        parts = rest.split(None, 1)
                        if parts and parts[0].isdigit() and len(parts) > 1:
                            code_part = parts[1]
                            
                            tokens = code_part.split()
                            source_start = 0
                            for i, token in enumerate(tokens):
                                if len(token) == 2 and all(c in '0123456789ABCDEFabcdef' for c in token):
                                    source_start = i + 1
                                else:
                                    break
                            
                            if source_start < len(tokens):
                                source = ' '.join(tokens[source_start:])
                                if source and not source.startswith(';'):
                                    self.lines.append(source)
        
        print(f"Parsed {len(self.lines)} instructions")
    
    def _generate_code(self):
        self.source_output = """// Auto-generated from CA65 listing
#include "SMB.hpp"

void SMBEngine::code(int mode)
{
    switch (mode)
    {
    case 0:
        loadConstantData();
        goto Reset;
    case 1:
        goto NMI;
    }

"""
        
        for source in self.lines:
            if ';' in source:
                source = source.split(';')[0].strip()
            
            if not source:
                continue
            
            if source.endswith(':'):
                label = source[:-1].strip()
                self.source_output += f"\n{label}:\n"
                continue
            
            if ('=' in source or source.startswith('.') or 
                any(x in source.upper() for x in ['APU_', 'PPU_', 'JOYPAD', 'OAM_'])):
                continue
            
            tokens = source.split()
            if tokens:
                inst = tokens[0].lower()
                operand = ' '.join(tokens[1:]) if len(tokens) > 1 else ""
                
                cpp_code = self._translate_instruction(inst, operand)
                if cpp_code:
                    self.source_output += f"{TAB}{cpp_code}\n"
        
        self.source_output += "\nReturn:\n"
        self.source_output += f"{TAB}switch (popReturnIndex())\n{TAB}{{\n"
        for i in range(self.return_label_index):
            self.source_output += f"{TAB}case {i}: goto Return_{i};\n"
        self.source_output += f"{TAB}}}\n}}\n"
    
    def _translate_instruction(self, inst: str, operand: str) -> str:
        
        if inst == 'lda':
            return f"a = {self._read_operand(operand)};"
        elif inst == 'ldx':
            return f"x = {self._read_operand(operand)};"
        elif inst == 'ldy':
            return f"y = {self._read_operand(operand)};"
        
        elif inst == 'sta':
            return f"writeData({self._write_address(operand)}, a);"
        elif inst == 'stx':
            return f"writeData({self._write_address(operand)}, x);"
        elif inst == 'sty':
            return f"writeData({self._write_address(operand)}, y);"
        
        elif inst == 'tax':
            return "x = a;"
        elif inst == 'tay':
            return "y = a;"
        elif inst == 'txa':
            return "a = x;"
        elif inst == 'tya':
            return "a = y;"
        elif inst == 'tsx':
            return "x = s;"
        elif inst == 'txs':
            return "s = x;"
        
        elif inst == 'pha':
            return "pha();"
        elif inst == 'pla':
            return "pla();"
        elif inst == 'php':
            return "php();"
        elif inst == 'plp':
            return "plp();"
        
        elif inst == 'inc':
            addr = self._write_address(operand)
            return f"writeData({addr}, M({addr}) + 1);"
        elif inst == 'dec':
            addr = self._write_address(operand)
            return f"writeData({addr}, M({addr}) - 1);"
        elif inst == 'inx':
            return "x = (x + 1) & 0xFF;"
        elif inst == 'iny':
            return "y = (y + 1) & 0xFF;"
        elif inst == 'dex':
            return "x = (x - 1) & 0xFF;"
        elif inst == 'dey':
            return "y = (y - 1) & 0xFF;"
        
        elif inst == 'adc':
            return f"a += {self._read_operand(operand)};"
        elif inst == 'sbc':
            return f"a -= {self._read_operand(operand)};"
        
        elif inst == 'and':
            return f"a &= {self._read_operand(operand)};"
        elif inst == 'ora':
            return f"a |= {self._read_operand(operand)};"
        elif inst == 'eor':
            return f"a ^= {self._read_operand(operand)};"
        elif inst == 'bit':
            return f"bit({self._read_operand(operand)});"
        
        elif inst == 'cmp':
            return f"compare(a, {self._read_operand(operand)});"
        elif inst == 'cpx':
            return f"compare(x, {self._read_operand(operand)});"
        elif inst == 'cpy':
            return f"compare(y, {self._read_operand(operand)});"
        
        elif inst == 'asl':
            if operand:
                addr = self._write_address(operand)
                return f"writeData({addr}, (M({addr}) << 1) & 0xFF);"
            else:
                return "a = (a << 1) & 0xFF;"
        elif inst == 'lsr':
            if operand:
                addr = self._write_address(operand)
                return f"writeData({addr}, M({addr}) >> 1);"
            else:
                return "a = a >> 1;"
        elif inst == 'rol':
            if operand:
                addr = self._write_address(operand)
                return f"writeData({addr}, ((M({addr}) << 1) | (c ? 1 : 0)) & 0xFF); c = (M({addr}) & 0x80) ? 1 : 0;"
            else:
                return "{ uint8_t temp = a; a = ((a << 1) | (c ? 1 : 0)) & 0xFF; c = (temp & 0x80) ? 1 : 0; }"
        elif inst == 'ror':
            if operand:
                addr = self._write_address(operand)
                return f"writeData({addr}, (M({addr}) >> 1) | (c ? 0x80 : 0)); c = (M({addr}) & 0x01) ? 1 : 0;"
            else:
                return "{ uint8_t temp = a; a = (a >> 1) | (c ? 0x80 : 0); c = (temp & 0x01) ? 1 : 0; }"
        
        elif inst == 'jmp':
            if operand.startswith('('):
                return f"/* indirect jump {operand} */"
            elif operand.startswith('a:$'):
                addr = operand[3:]
                return f"/* jump to absolute address 0x{addr} - label not found */"
            else:
                return f"goto {operand};"
        elif inst == 'jsr':
            if 'jump_engine' in operand.lower():
                return "/* JumpEngine switch */"
            else:
                ret_label = f"Return_{self.return_label_index}"
                self.return_label_index += 1
                return f"pushReturnIndex({self.return_label_index - 1});\n{TAB}goto {operand};\n{ret_label}:"
        elif inst == 'rts':
            return "goto Return;"
        elif inst == 'rti':
            return "return;"
        
        elif inst == 'bne':
            return f"if (!z) goto {operand};"
        elif inst == 'beq':
            return f"if (z) goto {operand};"
        elif inst == 'bcc':
            return f"if (!c) goto {operand};"
        elif inst == 'bcs':
            return f"if (c) goto {operand};"
        elif inst == 'bpl':
            return f"if (!n) goto {operand};"
        elif inst == 'bmi':
            return f"if (n) goto {operand};"
        elif inst == 'bvc':
            return f"if (!v) goto {operand};"
        elif inst == 'bvs':
            return f"if (v) goto {operand};"
        
        elif inst == 'clc':
            return "c = 0;"
        elif inst == 'sec':
            return "c = 1;"
        elif inst == 'cld':
            return "/* cld */;"
        elif inst == 'sed':
            return "/* sed */;"
        elif inst == 'cli':
            return "/* cli */;"
        elif inst == 'sei':
            return "/* sei */;"
        elif inst == 'clv':
            return "/* clv */;"
        
        elif inst == 'nop':
            return "; // nop"
        elif inst == 'brk':
            return "return;"
        
        else:
            return f"/* {inst} {operand} */;"
    
    def _read_operand(self, operand: str) -> str:
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        if operand.startswith('#'):
            val = operand[1:]
            return f"0x{val[1:]}" if val.startswith('$') else val
        
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '')
            addr = self._convert_address(base)
            return f"M({addr} + x)"
        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '')
            addr = self._convert_address(base)
            return f"M({addr} + y)"
        
        if operand.startswith('(') and operand.endswith(')'):
            addr = self._convert_address(operand[1:-1])
            return f"W({addr})"
        
        return f"M({self._convert_address(operand)})"
    
    def _write_address(self, operand: str) -> str:
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '')
            addr = self._convert_address(base)
            return f"{addr} + x"
        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '')
            addr = self._convert_address(base)
            return f"{addr} + y"
        
        return self._convert_address(operand)
    
    def _convert_address(self, addr: str) -> str:
        addr = addr.strip()
        
        if addr.startswith('a:') or addr.startswith('z:'):
            addr = addr[2:]
        
        if addr.startswith('$'):
            return f"0x{addr[1:]}"
        
        if addr.upper() in ['PPU_STATUS', 'PPU_CTRL', 'PPU_MASK', 'PPU_SCROLL', 
                          'PPU_ADDR', 'PPU_DATA', 'APU_SND_CHN', 'OAM_ADDR', 
                          'OAM_DMA', 'JOYPAD1', 'JOYPAD2']:
            return addr.upper()
        
        return addr
    
    def save_output(self, output_dir: str):
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        
        source_file = output_path / "SMB.cpp"
        with open(source_file, 'w') as f:
            f.write(self.source_output)
        
        print(f"Generated: {source_file}")

def main():
    if len(sys.argv) < 3:
        print("Usage: python listing_translator.py <listing_file> <output_dir>")
        sys.exit(1)
    
    translator = ListingTranslator(sys.argv[1])
    translator.save_output(sys.argv[2])
    print("Done!")

if __name__ == "__main__":
    main()
