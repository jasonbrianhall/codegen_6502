#!/usr/bin/env python3
"""
CA65 Listing to C++ Translator - Fixed Version
"""

import sys
import os
import re
from pathlib import Path

TAB = "    "

class ListingTranslator:
    def __init__(self, listing_file: str, config_dir: str = None):
        self.listing_file = listing_file
        self.lines = []
        self.return_label_index = 0
        self.source_output = ""
        self.symbols = {}  # Store symbol definitions
        
        self._parse_listing()
        self._generate_code()
    
    def _parse_listing(self):
        with open(self.listing_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line = line.rstrip()
                if not line or line.startswith('ca65') or line.startswith('Main') or line.startswith('Current') or line.startswith('------'):
                    continue
                
                # Parse symbol definitions like "_var_00fa_indexed = $00FA"
                if '=' in line and '$' in line and 'r 1' in line:
                    # Look for pattern: address r 1 spaces symbol = $value
                    match = re.search(r'r 1\s+([_a-zA-Z][_a-zA-Z0-9]*)\s*=\s*\$([0-9A-Fa-f]+)', line)
                    if match:
                        symbol_name = match.group(1)
                        hex_value = match.group(2).upper()
                        self.symbols[symbol_name] = f"0x{hex_value}"
                        print(f"Found symbol: {symbol_name} = {self.symbols[symbol_name]}")
                
                # Parse instruction lines
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
        
        print(f"Parsed {len(self.symbols)} symbols and {len(self.lines)} instructions")
    
    def _generate_code(self):
        self.source_output = """// Auto-generated from CA65 listing
#include "SMB.hpp"

// Missing processor status flags as global variables
extern uint8_t i;
extern uint8_t d;
extern uint8_t b;
extern uint8_t v;

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
                if len(tokens) >= 3 and tokens[0] == 'rr' and tokens[1] == 'rr':
                    inst = tokens[2].lower()
                    operand = ' '.join(tokens[3:]) if len(tokens) > 3 else ""
                else:
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
            # Load instructions - MUST set flags
            if inst == 'lda':
                return f"a = {self._read_operand(operand)}; setZN(a);"
            elif inst == 'ldx':
                return f"x = {self._read_operand(operand)}; setZN(x);"
            elif inst == 'ldy':
                return f"y = {self._read_operand(operand)}; setZN(y);"
        
            # Store instructions - no flag changes
            elif inst == 'sta':
                return f"writeData({self._write_address(operand)}, a);"
            elif inst == 'stx':
                return f"writeData({self._write_address(operand)}, x);"
            elif inst == 'sty':
                return f"writeData({self._write_address(operand)}, y);"
        
            # Transfer instructions - MUST set flags for destination
            elif inst == 'tax':
                return "x = a; setZN(x);"
            elif inst == 'tay':
                return "y = a; setZN(y);"
            elif inst == 'txa':
                return "a = x; setZN(a);"
            elif inst == 'tya':
                return "a = y; setZN(a);"
            elif inst == 'tsx':
                return "x = s; setZN(x);"
            elif inst == 'txs':
                return "s = x;"  # TXS doesn't affect flags
        
            # Stack instructions
            elif inst == 'pha':
                return "pha();"
            elif inst == 'pla':
                return "pla();"  # pla() will set flags internally
            elif inst == 'php':
                return "php();"
            elif inst == 'plp':
                return "plp();"
        
            # Increment/decrement - use proper functions that set flags
            elif inst == 'inc':
                return f"inc({self._write_address(operand)});"
            elif inst == 'dec':
                return f"dec({self._write_address(operand)});"
            elif inst == 'inx':
                return "++x; setZN(x);"
            elif inst == 'iny':
                return "++y; setZN(y);"
            elif inst == 'dex':
                return "--x; setZN(x);"
            elif inst == 'dey':    
                return "--y; setZN(y);"
        
            # Arithmetic - use proper functions that handle all flags
            elif inst == 'adc':    
                return f"adc({self._read_operand(operand)});"
            elif inst == 'sbc':
                return f"sbc({self._read_operand(operand)});"
        
            # Logical operations - MUST set N and Z flags
            elif inst == 'and':
                return f"a &= {self._read_operand(operand)}; setZN(a);"
            elif inst == 'ora':
                return f"a |= {self._read_operand(operand)}; setZN(a);"
            elif inst == 'eor':
                return f"a ^= {self._read_operand(operand)}; setZN(a);"
            elif inst == 'bit':
                return f"bit({self._read_operand(operand)});"
        
            # Compare operations - these should already set flags correctly
            elif inst == 'cmp':
                return f"compare(a, {self._read_operand(operand)});"
            elif inst == 'cpx':
                return f"compare(x, {self._read_operand(operand)});"
            elif inst == 'cpy':    
                return f"compare(y, {self._read_operand(operand)});"
        
            # Jump and branch instructions
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
        
            # Branch instructions - these check flags set by previous operations
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
        
            # Flag instructions
            elif inst == 'clc':
                return "c = 0;"
            elif inst == 'sec':
                return "c = 1;"
            elif inst == 'cld':
                return "d = 0;"
            elif inst == 'sed':
                return "d = 1;"
            elif inst == 'cli':
                return "i = 0;"    
            elif inst == 'sei':
                return "i = 1;"
            elif inst == 'clv':
                return "v = 0;"  # Actually clear the overflow flag
        
            # System instructions
            elif inst == 'nop':
                return "; // nop"
            elif inst == 'brk':
                return "return;"    

            #Shift instructions        
            elif inst == 'asl':
                if operand:
                    return f"asl({self._write_address(operand)});"
                else:
                    return "asl_acc();"
            elif inst == 'lsr':
                if operand:
                    return f"lsr({self._write_address(operand)});"
                else:
                    return "lsr_acc();"
            elif inst == 'rol':
                if operand:
                    return f"rol({self._write_address(operand)});"
                else:
                    return "rol_acc();"
            elif inst == 'ror':
                if operand:
                    return f"ror({self._write_address(operand)});"
                else:
                    return "ror_acc();"
        
        
            # Unofficial opcodes
            elif inst == 'lax':
                return f"a = {self._read_operand(operand)}; x = a; setZN(a);"
            elif inst == 'sax':
                return f"writeData({self._write_address(operand)}, a & x);"    
        
            else:
                return f"/* {inst} {operand} */;"
    

    def _read_operand(self, operand: str) -> str:
        if not operand:
            return "0"
    
        operand = operand.strip()
    
        # IMMEDIATE ADDRESSING - return the value directly, don't read from memory
        if operand.startswith('#'):
            val = operand[1:]
            if val.startswith('$'):
                return f"0x{val[1:]}"
            else:
                try:
                    # Try to parse as decimal
                    return str(int(val))
                except ValueError:
                    return val
    
        # INDEXED ADDRESSING
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            addr = self._convert_address(base)
            return f"M({addr} + x)"

        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            addr = self._convert_address(base)
            return f"M({addr} + y)"

        # INDIRECT ADDRESSING
        if operand.startswith('(') and operand.endswith(')'):
            inner_operand = operand[1:-1]
            addr = self._convert_address(inner_operand)
            return f"W({addr})"
    
        # ABSOLUTE/ZERO PAGE ADDRESSING - read from memory
        addr = self._convert_address(operand)
        return f"M({addr})"
    
    def _write_address(self, operand: str) -> str:
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            addr = self._convert_address(base)
            return f"{addr} + x"
        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            addr = self._convert_address(base)
            return f"{addr} + y"
        
        return self._convert_address(operand)
    
    def _convert_address(self, addr: str) -> str:
        addr = addr.strip()
        
        # Remove addressing mode prefixes
        if addr.startswith('a:') or addr.startswith('z:'):
            addr = addr[2:]
        
        # Handle direct hex addresses
        if addr.startswith('$'):
            return f"0x{addr[1:]}"
        
        # Handle known hardware registers
        if addr.upper() in ['PPU_STATUS', 'PPU_CTRL', 'PPU_MASK', 'PPU_SCROLL', 
                          'PPU_ADDR', 'PPU_DATA', 'APU_SND_CHN', 'OAM_ADDR', 
                          'OAM_DMA', 'JOYPAD1', 'JOYPAD2']:
            return addr.upper()
        
        # Look up symbols in our symbol table
        if addr in self.symbols:
            return self.symbols[addr]
        
        # If it's not in our symbol table but looks like a symbol, warn and try to extract hex
        if addr.startswith('_'):
            patterns = [
                r'_(?:var|data)_([0-9a-fA-F]{4})(?:_indexed)?',
                r'_([0-9a-fA-F]{4})_',
                r'_([0-9a-fA-F]{4})$'
            ]
            
            for pattern in patterns:
                match = re.search(pattern, addr, re.IGNORECASE)
                if match:
                    hex_addr = match.group(1).lower()
                    print(f"Warning: Symbol {addr} not in symbol table, using extracted address 0x{hex_addr}")
                    return f"0x{hex_addr}"
            
            print(f"Warning: Unknown symbol {addr}")
            return f"/* UNKNOWN: {addr} */ 0"
        
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
