#!/usr/bin/env python3
"""
CA65 Listing to C++ Translator
Converts CA65 listing files directly to C++ code for game engines
Much simpler than parsing raw assembly!
"""

import sys
import os
from pathlib import Path
from typing import Dict, List, Set, Optional, Tuple
from enum import Enum

class LineType(Enum):
    EMPTY = "empty"
    COMMENT = "comment"
    LABEL = "label"
    INSTRUCTION = "instruction"
    DATA = "data"
    DIRECTIVE = "directive"

class LabelType(Enum):
    CODE = "code"
    DATA = "data"
    ALIAS = "alias"

class ListingLine:
    """Represents a single line from the CA65 listing"""
    def __init__(self, line_num: int, raw_line: str):
        self.line_num = line_num
        self.raw_line = raw_line.rstrip('\n\r')
        self.address = None
        self.source_line = None
        self.bytes = None
        self.source_code = ""
        self.type = LineType.EMPTY
        self.label = None
        self.instruction = None
        self.operand = None
        self.comment = None
        
        self._parse_line()
    
    def _parse_line(self):
        """Parse the CA65 listing line format"""
        if not self.raw_line.strip():
            self.type = LineType.EMPTY
            return
        
        # Skip header lines
        if self.raw_line.startswith('ca65') or self.raw_line.startswith('------'):
            self.type = LineType.COMMENT
            return
        
        line = self.raw_line
        
        # Extract address (first 7 characters)
        addr_part = line[:7].strip()
        if addr_part and self._is_valid_address(addr_part):
            self.address = addr_part.rstrip('r')
        
        # Extract source line number (around column 8)
        rest = line[8:].lstrip()
        if rest:
            parts = rest.split(None, 1)
            if parts and parts[0].isdigit():
                self.source_line = int(parts[0])
                if len(parts) > 1:
                    rest = parts[1]
                else:
                    rest = ""
        
        # Extract hex bytes and source code
        if rest:
            hex_bytes, source_code = self._extract_hex_and_source(rest)
            if hex_bytes:
                self.bytes = hex_bytes
            self.source_code = source_code
        
        # If we still don't have source code, try the end of the line
        if not self.source_code and len(line) > 24:
            self.source_code = line[24:].strip()
        
        self._analyze_source()
    
    def _is_valid_address(self, s: str) -> bool:
        """Check if string looks like a valid address"""
        if not s:
            return False
        if s.endswith('r'):
            s = s[:-1]
        return len(s) > 0 and all(c in '0123456789ABCDEFabcdef' for c in s)
    
    def _extract_hex_and_source(self, text: str) -> Tuple[str, str]:
        """Extract hex bytes from start of text, return (hex_part, source_part)"""
        hex_part = ""
        i = 0
        
        # Skip leading whitespace
        while i < len(text) and text[i].isspace():
            i += 1
        
        # Extract hex bytes (2-char hex sequences)
        while i < len(text):
            # Skip whitespace between hex bytes
            while i < len(text) and text[i].isspace():
                hex_part += text[i]
                i += 1
            
            # Check for 2-character hex sequence
            if i + 1 < len(text):
                byte_str = text[i:i+2]
                if all(c in '0123456789ABCDEFabcdef' for c in byte_str):
                    hex_part += byte_str
                    i += 2
                else:
                    break
            else:
                break
        
        # The rest is source code (must have significant whitespace separation)
        source_part = text[i:]
        if source_part.startswith('  ') or source_part.startswith('\t'):
            return hex_part.strip(), source_part.strip()
        else:
            # No clear separation, treat everything as source
            return "", text.strip()
    
    def _analyze_source(self):
        """Analyze the source code portion"""
        if not self.source_code:
            self.type = LineType.EMPTY
            return
        
        # Extract comment
        if ';' in self.source_code:
            parts = self.source_code.split(';', 1)
            self.source_code = parts[0].strip()
            self.comment = parts[1].strip()
        
        if not self.source_code:
            self.type = LineType.COMMENT
            return
        
        # Check for labels
        if self.source_code.endswith(':'):
            self.type = LineType.LABEL
            self.label = self.source_code[:-1].strip()
            return
        
        # Check for labels with code on same line
        if ':' in self.source_code:
            colon_pos = self.source_code.find(':')
            potential_label = self.source_code[:colon_pos].strip()
            if self._is_valid_label_name(potential_label):
                self.label = potential_label
                rest = self.source_code[colon_pos + 1:].strip()
                if rest:
                    self.source_code = rest
                    self._analyze_instruction_or_data()
                else:
                    self.type = LineType.LABEL
                return
        
        self._analyze_instruction_or_data()
    
    def _is_valid_label_name(self, name: str) -> bool:
        """Check if string is a valid label name"""
        if not name:
            return False
        if not (name[0].isalpha() or name[0] == '_'):
            return False
        return all(c.isalnum() or c == '_' for c in name[1:])
    
    def _analyze_instruction_or_data(self):
        """Determine if this is an instruction or data"""
        tokens = self.source_code.lower().split()
        if not tokens:
            self.type = LineType.EMPTY
            return
        
        first_token = tokens[0]
        
        # Check for data directives
        if first_token in ['.byte', '.word', '.db', '.dw', '.res', '.addr']:
            self.type = LineType.DATA
            return
        
        # Check for other directives
        if first_token.startswith('.'):
            self.type = LineType.DIRECTIVE
            return
        
        # Check for 6502 instructions
        instructions = {
            'lda', 'ldx', 'ldy', 'sta', 'stx', 'sty',
            'tax', 'tay', 'txa', 'tya', 'tsx', 'txs',
            'pha', 'php', 'pla', 'plp', 'phx', 'phy', 'plx', 'ply',
            'and', 'eor', 'ora', 'bit',
            'adc', 'sbc', 'cmp', 'cpx', 'cpy',
            'inc', 'inx', 'iny', 'dec', 'dex', 'dey',
            'asl', 'lsr', 'rol', 'ror',
            'jmp', 'jsr', 'rts', 'rti', 'rtl',
            'bcc', 'bcs', 'beq', 'bmi', 'bne', 'bpl', 'bvc', 'bvs',
            'clc', 'cld', 'cli', 'clv', 'sec', 'sed', 'sei',
            'brk', 'nop', 'wdm', 'cop',
            # 65816 specific
            'brl', 'jml', 'jsl', 'mvn', 'mvp', 'pea', 'pei', 'per',
            'phb', 'phd', 'phk', 'plb', 'pld', 'rep', 'sep', 'tcd',
            'tcs', 'tdc', 'tsc', 'txy', 'tyx', 'xba', 'xce'
        }
        
        if first_token in instructions:
            self.type = LineType.INSTRUCTION
            self.instruction = first_token
            if len(tokens) > 1:
                self.operand = ' '.join(tokens[1:])
            return
        
        # Default to directive for unknown content
        self.type = LineType.DIRECTIVE

class ListingTranslator:
    """Main translator class"""
    
    def __init__(self, listing_file: str, config_dir: str = None):
        self.listing_file = listing_file
        self.config_dir = config_dir
        self.lines: List[ListingLine] = []
        self.labels: Dict[str, LabelType] = {}
        self.label_positions: Dict[str, int] = {}
        self.return_label_count = 0
        
        # Output buffers
        self.source_output = ""
        self.data_output = ""
        self.header_output = ""
        
        # Load configuration
        self._load_config()
        
        # Parse listing file
        self._parse_listing()
        
        # Classify labels
        self._classify_labels()
    
    def _load_config(self):
        """Load label configuration from files"""
        if not self.config_dir or not os.path.exists(self.config_dir):
            print(f"Warning: Config directory '{self.config_dir}' not found, using auto-classification")
            return
        
        # Load from ca65list.py output files
        config_files = {
            'code_labels.txt': LabelType.CODE,
            'data_labels.txt': LabelType.DATA,
            'alias_labels.txt': LabelType.ALIAS
        }
        
        for filename, label_type in config_files.items():
            file_path = Path(self.config_dir) / filename
            if file_path.exists():
                count = self._load_label_file(file_path, label_type)
                print(f"Loaded {count} {label_type.value} labels from {filename}")
    
    def _load_label_file(self, file_path: Path, label_type: LabelType) -> int:
        """Load labels from a configuration file"""
        count = 0
        try:
            with open(file_path, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        # Extract label name (remove comments)
                        if '#' in line:
                            line = line.split('#')[0].strip()
                        if line:
                            self.labels[line] = label_type
                            count += 1
        except Exception as e:
            print(f"Warning: Could not load {file_path}: {e}")
        return count
    
    def _parse_listing(self):
        """Parse the CA65 listing file"""
        try:
            with open(self.listing_file, 'r', encoding='utf-8', errors='ignore') as f:
                for line_num, raw_line in enumerate(f, 1):
                    line_obj = ListingLine(line_num, raw_line)
                    self.lines.append(line_obj)
                    
                    # Track label positions
                    if line_obj.label:
                        self.label_positions[line_obj.label] = len(self.lines) - 1
            
            print(f"Parsed {len(self.lines)} lines from {self.listing_file}")
            print(f"Found {len(self.label_positions)} labels")
            
        except FileNotFoundError:
            print(f"Error: Could not find listing file {self.listing_file}")
            print("Generate it with: ca65 -l output.lst input.asm")
            sys.exit(1)
    
    def _classify_labels(self):
        """Classify labels as code, data, or alias"""
        print("Classifying labels...")
        
        for label_name, pos in self.label_positions.items():
            if label_name not in self.labels:
                # Auto-classify by analyzing what follows
                self.labels[label_name] = self._auto_classify_label(label_name, pos)
        
        # Print classification summary
        code_count = sum(1 for t in self.labels.values() if t == LabelType.CODE)
        data_count = sum(1 for t in self.labels.values() if t == LabelType.DATA)
        alias_count = sum(1 for t in self.labels.values() if t == LabelType.ALIAS)
        
        print(f"Label classification: {code_count} CODE, {data_count} DATA, {alias_count} ALIAS")
    
    def _auto_classify_label(self, label_name: str, start_pos: int) -> LabelType:
        """Auto-classify a label by analyzing what follows it"""
        data_count = 0
        instruction_count = 0
        alias_target = None
        
        # Look at next 20 lines
        for i in range(start_pos + 1, min(len(self.lines), start_pos + 21)):
            line = self.lines[i]
            
            # Stop at next label
            if line.label and line.label != label_name:
                break
            
            if line.type == LineType.INSTRUCTION:
                instruction_count += 1
                # Check for simple aliases (single jmp/jsr)
                if (instruction_count == 1 and data_count == 0 and 
                    line.instruction in ['jmp', 'jsr'] and line.operand):
                    alias_target = line.operand.strip()
            elif line.type == LineType.DATA:
                data_count += 1
        
        # Classification logic
        if alias_target and instruction_count == 1 and data_count == 0:
            return LabelType.ALIAS
        elif data_count > 0 and instruction_count == 0:
            return LabelType.DATA
        elif data_count > instruction_count and data_count >= 3:
            return LabelType.DATA
        else:
            return LabelType.CODE
    
    def translate(self):
        """Main translation entry point"""
        print("Translating to C++...")
        
        self._generate_headers()
        self._generate_data_section()
        self._generate_code_section()
        
        print("Translation complete!")
    
    def _generate_headers(self):
        """Generate C++ headers"""
        self.header_output = """// Auto-generated from CA65 listing file
// Do not edit directly

#ifndef SMB_GENERATED_HPP
#define SMB_GENERATED_HPP

#include <cstdint>

// Data pointers
"""
        
        # Generate data pointer declarations
        for label_name, label_type in self.labels.items():
            if label_type == LabelType.DATA:
                self.header_output += f"extern uint16_t {label_name}_ptr;\n"
        
        self.header_output += "\n#endif // SMB_GENERATED_HPP\n"
    
    def _generate_data_section(self):
        """Generate data loading code"""
        self.data_output = """// Auto-generated data loading code
#include "SMB.hpp"

void SMBEngine::loadConstantData()
{
"""
        
        storage_address = 0x8000
        
        for label_name, label_type in self.labels.items():
            if label_type != LabelType.DATA:
                continue
            
            pos = self.label_positions.get(label_name)
            if pos is None:
                continue
            
            # Generate data array
            data_bytes = self._extract_data_bytes(pos)
            if not data_bytes:
                continue
            
            self.data_output += f"\n    // {label_name}\n"
            self.data_output += f"    const uint8_t {label_name}_data[] = {{\n"
            
            # Output bytes in rows of 16
            for i in range(0, len(data_bytes), 16):
                row = data_bytes[i:i+16]
                self.data_output += "        "
                self.data_output += ", ".join(f"0x{b:02X}" for b in row)
                if i + 16 < len(data_bytes):
                    self.data_output += ","
                self.data_output += "\n"
            
            self.data_output += f"    }};\n"
            self.data_output += f"    writeData({label_name}_ptr, {label_name}_data, sizeof({label_name}_data));\n"
            
            storage_address += len(data_bytes)
        
        self.data_output += "}\n"
    
    def _extract_data_bytes(self, start_pos: int) -> List[int]:
        """Extract data bytes following a label"""
        bytes_list = []
        
        for i in range(start_pos + 1, len(self.lines)):
            line = self.lines[i]
            
            # Stop at next label
            if line.label:
                break
            
            # Process data lines
            if line.type == LineType.DATA and line.bytes:
                # Parse hex bytes
                hex_str = line.bytes.replace(' ', '')
                for j in range(0, len(hex_str), 2):
                    if j + 1 < len(hex_str):
                        byte_val = int(hex_str[j:j+2], 16)
                        bytes_list.append(byte_val)
        
        return bytes_list
    
    def _generate_code_section(self):
        """Generate main C++ code"""
        self.source_output = """// Auto-generated code from CA65 listing
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
        
        # Generate code for each code label
        for label_name, label_type in self.labels.items():
            if label_type != LabelType.CODE:
                continue
            
            pos = self.label_positions.get(label_name)
            if pos is None:
                continue
            
            self.source_output += f"\n{label_name}:\n"
            
            # Translate instructions following this label
            for i in range(pos + 1, len(self.lines)):
                line = self.lines[i]
                
                # Stop at next label
                if line.label:
                    break
                
                if line.type == LineType.INSTRUCTION:
                    translated = self._translate_instruction(line)
                    self.source_output += f"    {translated}"
                    
                    if line.comment:
                        self.source_output += f" // {line.comment}"
                    
                    self.source_output += "\n"
        
        # Generate return handler
        self.source_output += "\n// Return handler\nReturn:\n"
        self.source_output += "    switch (popReturnIndex())\n    {\n"
        
        for i in range(self.return_label_count):
            self.source_output += f"    case {i}:\n        goto Return_{i};\n"
        
        self.source_output += "    }\n}\n"
    
    def _translate_instruction(self, line: ListingLine) -> str:
        """Translate a single 6502 instruction to C++"""
        inst = line.instruction
        operand = line.operand or ""
        
        # Load instructions
        if inst == 'lda':
            return f"a = {self._translate_operand(operand)};"
        elif inst == 'ldx':
            return f"x = {self._translate_operand(operand)};"
        elif inst == 'ldy':
            return f"y = {self._translate_operand(operand)};"
        
        # Store instructions
        elif inst == 'sta':
            return f"writeData({self._translate_address(operand)}, a);"
        elif inst == 'stx':
            return f"writeData({self._translate_address(operand)}, x);"
        elif inst == 'sty':
            return f"writeData({self._translate_address(operand)}, y);"
        
        # Transfer instructions
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
        
        # Stack instructions
        elif inst == 'pha':
            return "pha();"
        elif inst == 'php':
            return "php();"
        elif inst == 'pla':
            return "pla();"
        elif inst == 'plp':
            return "plp();"
        
        # Arithmetic/Logic
        elif inst == 'adc':
            return f"a += {self._translate_operand(operand)};"
        elif inst == 'sbc':
            return f"a -= {self._translate_operand(operand)};"
        elif inst == 'and':
            return f"a &= {self._translate_operand(operand)};"
        elif inst == 'eor':
            return f"a ^= {self._translate_operand(operand)};"
        elif inst == 'ora':
            return f"a |= {self._translate_operand(operand)};"
        
        # Compare
        elif inst == 'cmp':
            return f"compare(a, {self._translate_operand(operand)});"
        elif inst == 'cpx':
            return f"compare(x, {self._translate_operand(operand)});"
        elif inst == 'cpy':
            return f"compare(y, {self._translate_operand(operand)});"
        
        # Increment/Decrement
        elif inst == 'inc':
            return f"++{self._translate_address(operand)};"
        elif inst == 'inx':
            return "++x;"
        elif inst == 'iny':
            return "++y;"
        elif inst == 'dec':
            return f"--{self._translate_address(operand)};"
        elif inst == 'dex':
            return "--x;"
        elif inst == 'dey':
            return "--y;"
        
        # Shifts
        elif inst == 'asl':
            if operand:
                return f"{self._translate_address(operand)} <<= 1;"
            else:
                return "a <<= 1;"
        elif inst == 'lsr':
            if operand:
                return f"{self._translate_address(operand)} >>= 1;"
            else:
                return "a >>= 1;"
        
        # Jumps and branches
        elif inst == 'jmp':
            if operand.startswith('('):
                return f"/* indirect jump: {operand} */"
            else:
                return f"goto {operand};"
        
        elif inst == 'jsr':
            if operand == 'JumpEngine':
                return "/* JumpEngine - implement switch */"
            else:
                ret_label = f"Return_{self.return_label_count}"
                self.return_label_count += 1
                return f"pushReturnIndex({self.return_label_count - 1}); goto {operand};\n{ret_label}:"
        
        elif inst == 'rts':
            return "goto Return;"
        
        # Branches
        elif inst == 'bcc':
            return f"if (!c) goto {operand};"
        elif inst == 'bcs':
            return f"if (c) goto {operand};"
        elif inst == 'beq':
            return f"if (z) goto {operand};"
        elif inst == 'bne':
            return f"if (!z) goto {operand};"
        elif inst == 'bmi':
            return f"if (n) goto {operand};"
        elif inst == 'bpl':
            return f"if (!n) goto {operand};"
        
        # Flags
        elif inst == 'clc':
            return "c = 0;"
        elif inst == 'sec':
            return "c = 1;"
        elif inst == 'cli':
            return "/* cli */;"
        elif inst == 'sei':
            return "/* sei */;"
        elif inst == 'cld':
            return "/* cld */;"
        elif inst == 'sed':
            return "d = 1;"
        
        # System
        elif inst == 'nop':
            return "; // nop"
        elif inst == 'brk':
            return "return;"
        elif inst == 'rti':
            return "return;"
        
        else:
            return f"/* {inst} {operand} */;"
    
    def _translate_operand(self, operand: str) -> str:
        """Translate an operand for reading"""
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        # Immediate addressing
        if operand.startswith('#'):
            value = operand[1:]
            if value.startswith('$'):
                return f"0x{value[1:]}"
            elif value.startswith('<'):
                return f"LOBYTE({value[1:]})"
            elif value.startswith('>'):
                return f"HIBYTE({value[1:]})"
            else:
                return value
        
        # Indexed addressing
        elif ',x' in operand.lower():
            base = operand.lower().replace(',x', '')
            return f"M({base} + x)"
        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '')
            return f"M({base} + y)"
        
        # Indirect addressing
        elif operand.startswith('(') and operand.endswith(')'):
            addr = operand[1:-1]
            if ',x)' in operand.lower():
                base = addr.replace(',x', '')
                return f"W({base} + x)"
            elif '),y' in operand.lower():
                base = addr.replace(',y', '')
                return f"W({base}) + y"
            else:
                return f"W({addr})"
        
        # Direct addressing
        else:
            if operand.startswith('$'):
                return f"M(0x{operand[1:]})"
            else:
                return f"M({operand})"
    
    def _translate_address(self, operand: str) -> str:
        """Translate an operand for addressing (no M() wrapper)"""
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        # Indexed addressing
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '')
            if base.startswith('$'):
                return f"0x{base[1:]} + x"
            else:
                return f"{base} + x"
        elif ',y' in operand.lower():
            base = operand.lower().replace(',y', '')
            if base.startswith('$'):
                return f"0x{base[1:]} + y"
            else:
                return f"{base} + y"
        
        # Direct addressing
        else:
            if operand.startswith('$'):
                return f"0x{operand[1:]}"
            else:
                return operand
    
    def save_output(self, output_dir: str):
        """Save all generated files"""
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        
        # Save header file
        header_file = output_path / "SMBGenerated.hpp"
        with open(header_file, 'w') as f:
            f.write(self.header_output)
        
        # Save data file
        data_file = output_path / "SMBData.cpp"
        with open(data_file, 'w') as f:
            f.write(self.data_output)
        
        # Save source file
        source_file = output_path / "SMB.cpp"
        with open(source_file, 'w') as f:
            f.write(self.source_output)
        
        print(f"Generated files in {output_dir}:")
        print("  SMBGenerated.hpp")
        print("  SMBData.cpp")
        print("  SMB.cpp")

def main():
    """Main entry point"""
    if len(sys.argv) < 3:
        print("Usage: python listing_translator.py <listing_file> <output_dir> [config_dir]")
        print("")
        print("Arguments:")
        print("  listing_file  - CA65 listing file (.lst)")
        print("  output_dir    - Directory for generated C++ files")
        print("  config_dir    - Directory with label configuration files (optional)")
        print("")
        print("Generate listing file with: ca65 -l output.lst input.asm")
        print("")
        print("Examples:")
        print("  python listing_translator.py duckhunt.lst output")
        print("  python listing_translator.py duckhunt.lst output listing_config")
        sys.exit(1)
    
    listing_file = sys.argv[1]
    output_dir = sys.argv[2]
    config_dir = sys.argv[3] if len(sys.argv) > 3 else None
    
    if not os.path.exists(listing_file):
        print(f"Error: Listing file '{listing_file}' not found")
        print("Generate it with: ca65 -l output.lst input.asm")
        sys.exit(1)
    
    try:
        # Create translator
        translator = ListingTranslator(listing_file, config_dir)
        
        # Translate to C++
        translator.translate()
        
        # Save output files
        translator.save_output(output_dir)
        
        print("\nTranslation completed successfully!")
        
        if config_dir:
            print(f"\nUsing config from: {config_dir}")
            print("To regenerate label configuration, run:")
            print(f"  python ca65list.py {listing_file} {config_dir}")
        else:
            print("\nTo improve label classification, run:")
            print(f"  python ca65list.py {listing_file}")
            print("  Then use the generated config directory with this translator")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
