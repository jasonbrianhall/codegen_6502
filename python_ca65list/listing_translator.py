#!/usr/bin/env python3
"""
Enhanced CA65 Listing to C++ Translator
Generates all required files and fixes compilation errors
"""

import sys
import os
import re
from pathlib import Path

TAB = "    "

class EnhancedListingTranslator:
    def __init__(self, listing_file, config_dir=None):
        self.listing_file = listing_file
        self.config_dir = config_dir
        self.lines = []
        self.return_label_index = 0
        
        # Output content
        self.source_output = ""
        self.data_output = ""
        self.data_header_output = ""
        self.constants_header_output = ""
        
        # Data tracking
        self.symbols = {}
        self.labels = {}
        self.data_labels = set()
        self.code_labels = set()
        self.storage_address = 0x8000
        self.data_sections = {}
        
        # Process everything
        self.load_config()
        self.parse_listing()
        self.classify_labels()
        self.generate_all_outputs()
    
    def load_config(self):
        """Load configuration files"""
        if not self.config_dir or not os.path.exists(self.config_dir):
            print("No config directory - using auto-classification")
            return
        
        # Load data labels
        data_file = Path(self.config_dir) / "data_labels.txt"
        if data_file.exists():
            with open(data_file, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        label = line.split('#')[0].strip()
                        if label:
                            self.data_labels.add(label)
            print(f"Loaded {len(self.data_labels)} data labels")
        
        # Load code labels
        code_file = Path(self.config_dir) / "code_labels.txt"
        if code_file.exists():
            with open(code_file, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        label = line.split('#')[0].strip()
                        if label:
                            self.code_labels.add(label)
            print(f"Loaded {len(self.code_labels)} code labels")
    
    def parse_listing(self):
        """Parse the CA65 listing file"""
        current_label = None
        current_data = []
        
        with open(self.listing_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line = line.rstrip()
                if not line or line.startswith('ca65') or line.startswith('Main') or line.startswith('Current') or line.startswith('------'):
                    continue
                
                # Parse symbol definitions
                if '=' in line and '$' in line and 'r 1' in line:
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
                            hex_bytes = []
                            
                            # Extract hex bytes
                            for i, token in enumerate(tokens):
                                if len(token) == 2 and all(c in '0123456789ABCDEFabcdef' for c in token):
                                    hex_bytes.append(token)
                                    source_start = i + 1
                                else:
                                    break
                            
                            if source_start < len(tokens):
                                source = ' '.join(tokens[source_start:])
                                if source and not source.startswith(';'):
                                    # Check if this is a label
                                    if source.endswith(':'):
                                        # Save previous label data
                                        if current_label and current_data:
                                            self.data_sections[current_label] = current_data.copy()
                                        
                                        # Start new label
                                        current_label = source[:-1].strip()
                                        current_data = []
                                        self.labels[current_label] = {
                                            'line': line_num,
                                            'source': source,
                                            'instructions': [],
                                            'data_bytes': []
                                        }
                                    else:
                                        # This is an instruction or data
                                        self.lines.append(source)
                                        
                                        # Track data for current label
                                        if current_label and hex_bytes:
                                            if any(source.strip().lower().startswith(d) for d in ['.db', '.dw', '.byte', '.word']):
                                                for hex_byte in hex_bytes:
                                                    current_data.append(int(hex_byte, 16))
                                                self.labels[current_label]['data_bytes'].extend(hex_bytes)
                                            else:
                                                self.labels[current_label]['instructions'].append(source)
        
        # Save final label data
        if current_label and current_data:
            self.data_sections[current_label] = current_data.copy()
        
        print(f"Parsed {len(self.symbols)} symbols, {len(self.lines)} instructions, {len(self.labels)} labels")
    
    def classify_labels(self):
        """Classify labels as code or data"""
        for label_name, label_info in self.labels.items():
            if label_name in self.data_labels:
                label_info['type'] = 'data'
            elif label_name in self.code_labels:
                label_info['type'] = 'code'
            else:
                # Auto-classify
                if label_info['data_bytes'] and not label_info['instructions']:
                    label_info['type'] = 'data'
                elif label_info['instructions']:
                    label_info['type'] = 'code'
                else:
                    label_info['type'] = 'code'  # Default to code
    
    def generate_all_outputs(self):
        """Generate all output files"""
        self.generate_constants_header()
        self.generate_data_files()
        self.generate_source_code()
    
    def generate_constants_header(self):
        """Generate constants header"""
        self.constants_header_output = """// Auto-generated from CA65 listing
#ifndef SMBCONSTANTS_HPP
#define SMBCONSTANTS_HPP

// Symbol definitions
"""
        
        # Add symbols
        for symbol_name, symbol_value in sorted(self.symbols.items()):
            self.constants_header_output += f"#define {symbol_name} {symbol_value}\n"
        
        # Add hardware addresses
        self.constants_header_output += """
// NES hardware addresses
#define PPU_CTRL 0x2000
#define PPU_MASK 0x2001
#define PPU_STATUS 0x2002
#define OAM_ADDR 0x2003
#define OAM_DATA 0x2004
#define PPU_SCROLL 0x2005
#define PPU_ADDR 0x2006
#define PPU_DATA 0x2007
#define APU_SND_CHN 0x4015
#define OAM_DMA 0x4014
#define JOYPAD1 0x4016
#define JOYPAD2 0x4017

// Address constants
"""
        
        # Collect address patterns from code
        hex_addresses = set()
        data_addresses = set()
        func_addresses = set()
        
        for source in self.lines:
            # Find hex patterns
            hex_matches = re.findall(r'\$([0-9A-Fa-f]{4})', source)
            for h in hex_matches:
                hex_addresses.add(h.upper())
            
            # Find data patterns
            data_matches = re.findall(r'_data_([0-9A-Fa-f]{4})', source, re.IGNORECASE)
            for h in data_matches:
                data_addresses.add(h.upper())
            
            # Find function patterns
            func_matches = re.findall(r'_func_([0-9A-Fa-f]{4})', source, re.IGNORECASE)
            for h in func_matches:
                func_addresses.add(h.upper())
        
        # Add label patterns
        for label_name in self.labels.keys():
            data_matches = re.findall(r'_data_([0-9A-Fa-f]{4})', label_name, re.IGNORECASE)
            for h in data_matches:
                data_addresses.add(h.upper())
            
            func_matches = re.findall(r'_func_([0-9A-Fa-f]{4})', label_name, re.IGNORECASE)
            for h in func_matches:
                func_addresses.add(h.upper())
        
        # Define constants
        for addr in sorted(hex_addresses):
            self.constants_header_output += f"#define ADDR_{addr} 0x{addr}\n"
        
        for addr in sorted(data_addresses):
            self.constants_header_output += f"#define DATA_{addr} 0x{addr}\n"
        
        for addr in sorted(func_addresses):
            self.constants_header_output += f"#define FUNC_{addr} 0x{addr}\n"
        
        self.constants_header_output += "\n#endif // SMBCONSTANTS_HPP\n"
    
    def generate_data_files(self):
        """Generate data header and implementation"""
        # Data header
        self.data_header_output = """// Auto-generated from CA65 listing
#ifndef SMBDATAPOINTERS_HPP
#define SMBDATAPOINTERS_HPP

struct SMBDataPointers
{
"""
        
        # Data implementation
        self.data_output = """// Auto-generated from CA65 listing
#include "SMB.hpp"

void SMBEngine::loadConstantData()
{
"""
        
        address_defines = "\n// Address defines\n"
        constructor_defaults = f"{TAB}SMBDataPointers()\n{TAB}{{\n"
        current_address = self.storage_address
        
        # Process data labels
        for label_name, label_info in self.labels.items():
            if label_info.get('type') == 'data' and label_name in self.data_sections:
                data_bytes = self.data_sections[label_name]
                if not data_bytes:
                    continue
                
                # Generate data array
                self.data_output += f"{TAB}// {label_name}\n"
                self.data_output += f"{TAB}const uint8_t {label_name}_data[] = {{"
                
                for i, byte_val in enumerate(data_bytes):
                    if i % 16 == 0:
                        self.data_output += f"\n{TAB}{TAB}"
                    self.data_output += f"0x{byte_val:02X}"
                    if i < len(data_bytes) - 1:
                        self.data_output += ", "
                
                self.data_output += f"\n{TAB}}};\n"
                self.data_output += f"{TAB}writeData({label_name}, {label_name}_data, sizeof({label_name}_data));\n\n"
                
                # Add to structures
                self.data_header_output += f"{TAB}uint16_t {label_name}_ptr;\n"
                address_defines += f"#define {label_name} (dataPointers.{label_name}_ptr)\n"
                constructor_defaults += f"{TAB}{TAB}this->{label_name}_ptr = 0x{current_address:x};\n"
                current_address += len(data_bytes)
        
        # Close data loading
        self.data_output += "}\n"
        
        # Close header
        self.data_header_output += f"{TAB}uint16_t freeSpaceAddress;\n"
        constructor_defaults += f"{TAB}{TAB}this->freeSpaceAddress = 0x{current_address:x};\n"
        constructor_defaults += f"{TAB}}}\n"
        self.data_header_output += f"\n{constructor_defaults}}};\n"
        self.data_header_output += address_defines
        self.data_header_output += "\n#endif // SMBDATAPOINTERS_HPP\n"
    
    def generate_source_code(self):
        """Generate main C++ source"""
        self.source_output = """// Auto-generated from CA65 listing
#include "SMB.hpp"

// Processor status flags
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
        
        # Find referenced labels
        referenced_labels = set()
        for source in self.lines:
            # Find goto targets
            if 'goto' in source:
                tokens = source.split()
                for token in tokens:
                    label = token.replace('goto', '').strip().rstrip(';')
                    if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', label):
                        referenced_labels.add(label)
            
            # Find branch targets
            for branch in ['bne', 'beq', 'bcc', 'bcs', 'bpl', 'bmi', 'bvc', 'bvs']:
                if source.strip().startswith(branch):
                    tokens = source.split()
                    if len(tokens) >= 2:
                        target = tokens[1].strip().rstrip(';')
                        if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', target):
                            referenced_labels.add(target)
            
            # Find JSR targets
            if 'jsr' in source.lower():
                tokens = source.split()
                if len(tokens) >= 2:
                    target = tokens[1].strip()
                    if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', target):
                        referenced_labels.add(target)
        
        # Generate code labels
        generated_labels = set()
        for label_name, label_info in self.labels.items():
            if label_info.get('type') == 'code':
                self.source_output += f"\n{label_name}:\n"
                generated_labels.add(label_name)
                
                for instruction in label_info.get('instructions', []):
                    cpp_code = self.translate_instruction_line(instruction)
                    if cpp_code:
                        self.source_output += f"{TAB}{cpp_code}\n"
        
        # Process remaining code
        current_label = None
        for source in self.lines:
            if ';' in source:
                source = source.split(';')[0].strip()
            
            if not source:
                continue
            
            if source.endswith(':'):
                label = source[:-1].strip()
                current_label = label
                if (label not in generated_labels and 
                    (label not in self.labels or self.labels[label].get('type') != 'data')):
                    self.source_output += f"\n{label}:\n"
                    generated_labels.add(label)
                continue
            
            if ('=' in source or source.startswith('.') or 
                any(x in source.upper() for x in ['APU_', 'PPU_', 'JOYPAD', 'OAM_'])):
                continue
            
            if (current_label is None or 
                current_label not in self.labels or 
                self.labels[current_label].get('type') != 'data'):
                
                cpp_code = self.translate_instruction_line(source)
                if cpp_code:
                    self.source_output += f"{TAB}{cpp_code}\n"
        
        # Generate stubs for missing labels
        missing_labels = referenced_labels - generated_labels
        if missing_labels:
            self.source_output += "\n// Stub labels\n"
            for label in sorted(missing_labels):
                if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', label):
                    self.source_output += f"\n{label}:\n"
                    self.source_output += f"{TAB}// TODO: Implement {label}\n"
                    self.source_output += f"{TAB}return;\n"
        
        # Return handler
        self.source_output += "\nReturn:\n"
        self.source_output += f"{TAB}switch (popReturnIndex())\n{TAB}{{\n"
        for i in range(self.return_label_index):
            self.source_output += f"{TAB}case {i}: goto Return_{i};\n"
        self.source_output += f"{TAB}}}\n}}\n"
    
    def translate_instruction_line(self, source):
        """Translate instruction line to C++"""
        tokens = source.split()
        if not tokens:
            return ""
        
        # Handle different instruction formats
        if len(tokens) >= 3 and tokens[0] == 'rr' and tokens[1] == 'rr':
            inst = tokens[2].lower()
            operand = ' '.join(tokens[3:]) if len(tokens) > 3 else ""
        else:
            inst = tokens[0].lower()
            operand = ' '.join(tokens[1:]) if len(tokens) > 1 else ""
        
        # Fix operand before translation
        if operand:
            operand = self.fix_operand_identifiers(operand)
        
        return self.translate_instruction(inst, operand)
    
    def fix_operand_identifiers(self, operand):
        """Fix invalid C++ identifiers in operands"""
        if not operand:
            return operand
        
        # Handle immediate addressing with hex values
        if operand.startswith('#$'):
            hex_part = operand[2:]
            if len(hex_part) == 4 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                return f"#ADDR_{hex_part.upper()}"
            elif len(hex_part) <= 2 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                return f"#0x{hex_part.upper()}"
        
        # Handle direct hex addresses
        if operand.startswith('$'):
            hex_part = operand[1:]
            if len(hex_part) == 4 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                return f"ADDR_{hex_part.upper()}"
            elif len(hex_part) <= 2 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                return f"0x{hex_part.upper()}"
        
        # Handle indexed addressing with hex
        if ',' in operand:
            parts = operand.split(',')
            if len(parts) == 2:
                base = parts[0].strip()
                index = parts[1].strip()
                
                # Fix the base part
                if base.startswith('$'):
                    hex_part = base[1:]
                    if len(hex_part) == 4 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                        base = f"ADDR_{hex_part.upper()}"
                    elif len(hex_part) <= 2 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                        base = f"0x{hex_part.upper()}"
                
                return f"{base},{index}"
        
        # Handle indirect addressing
        if operand.startswith('(') and operand.endswith(')'):
            inner = operand[1:-1]
            if inner.startswith('$'):
                hex_part = inner[1:]
                if len(hex_part) == 4 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                    return f"(ADDR_{hex_part.upper()})"
                elif len(hex_part) <= 2 and all(c in '0123456789ABCDEFabcdef' for c in hex_part):
                    return f"(0x{hex_part.upper()})"
        
        # Handle invalid identifier patterns
        operand = re.sub(r'_data_([0-9a-fA-F]{4})', r'DATA_\1', operand, flags=re.IGNORECASE)
        operand = re.sub(r'_func_([0-9a-fA-F]{4})', r'FUNC_\1', operand, flags=re.IGNORECASE)
        
        return operand
    
    def translate_instruction(self, inst, operand):
        """Translate 6502 instruction to C++"""
        # Load instructions
        if inst == 'lda':
            return f"a = {self.read_operand(operand)}; setZN(a);"
        elif inst == 'ldx':
            return f"x = {self.read_operand(operand)}; setZN(x);"
        elif inst == 'ldy':
            return f"y = {self.read_operand(operand)}; setZN(y);"
        
        # Store instructions
        elif inst == 'sta':
            return f"writeData({self.write_address(operand)}, a);"
        elif inst == 'stx':
            return f"writeData({self.write_address(operand)}, x);"
        elif inst == 'sty':
            return f"writeData({self.write_address(operand)}, y);"
        
        # Transfer instructions
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
            return "s = x;"
        
        # Stack instructions
        elif inst == 'pha':
            return "pha();"
        elif inst == 'pla':
            return "pla();"
        elif inst == 'php':
            return "php();"
        elif inst == 'plp':
            return "plp();"
        
        # Arithmetic
        elif inst == 'adc':
            return f"adc({self.read_operand(operand)});"
        elif inst == 'sbc':
            return f"sbc({self.read_operand(operand)});"
        
        # Logical
        elif inst == 'and':
            return f"a &= {self.read_operand(operand)}; setZN(a);"
        elif inst == 'ora':
            return f"a |= {self.read_operand(operand)}; setZN(a);"
        elif inst == 'eor':
            return f"a ^= {self.read_operand(operand)}; setZN(a);"
        elif inst == 'bit':
            return f"bit({self.read_operand(operand)});"
        
        # Compare
        elif inst == 'cmp':
            return f"compare(a, {self.read_operand(operand)});"
        elif inst == 'cpx':
            return f"compare(x, {self.read_operand(operand)});"
        elif inst == 'cpy':
            return f"compare(y, {self.read_operand(operand)});"
        
        # Increment/decrement
        elif inst == 'inc':
            return f"inc({self.write_address(operand)});"
        elif inst == 'dec':
            return f"dec({self.write_address(operand)});"
        elif inst == 'inx':
            return "++x; setZN(x);"
        elif inst == 'iny':
            return "++y; setZN(y);"
        elif inst == 'dex':
            return "--x; setZN(x);"
        elif inst == 'dey':
            return "--y; setZN(y);"
        
        # Shifts
        elif inst == 'asl':
            if operand:
                return f"asl({self.write_address(operand)});"
            else:
                return "asl_acc();"
        elif inst == 'lsr':
            if operand:
                return f"lsr({self.write_address(operand)});"
            else:
                return "lsr_acc();"
        elif inst == 'rol':
            if operand:
                return f"rol({self.write_address(operand)});"
            else:
                return "rol_acc();"
        elif inst == 'ror':
            if operand:
                return f"ror({self.write_address(operand)});"
            else:
                return "ror_acc();"
        
        # Jumps and branches
        elif inst == 'jmp':
            if operand.startswith('('):
                return f"/* indirect jump {operand} */"
            else:
                return f"goto {operand};"
        elif inst == 'jsr':
            ret_label = f"Return_{self.return_label_index}"
            self.return_label_index += 1
            return f"pushReturnIndex({self.return_label_index - 1});\n{TAB}goto {operand};\n{ret_label}:"
        elif inst == 'rts':
            return "goto Return;"
        elif inst == 'rti':
            return "return;"
        
        # Branches
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
        
        # Flags
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
            return "v = 0;"
        
        # System
        elif inst == 'nop':
            return "; // nop"
        elif inst == 'brk':
            return "return;"
        
        else:
            return f"/* {inst} {operand} */;"
    
    def read_operand(self, operand):
        """Convert operand for reading"""
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        # Immediate addressing
        if operand.startswith('#'):
            val = operand[1:]
            # Check if already a constant
            if (val.startswith('ADDR_') or val.startswith('DATA_') or 
                val.startswith('FUNC_') or val.startswith('0x')):
                return val
            elif val.startswith('$'):
                return f"0x{val[1:]}"
            else:
                try:
                    return str(int(val))
                except ValueError:
                    return val
        
        # Indexed addressing
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            
            if (base.startswith('ADDR_') or base.startswith('DATA_') or 
                base.startswith('FUNC_') or base.startswith('0x')):
                return f"M({base} + x)"
            else:
                addr = self.convert_address(base)
                return f"M({addr} + x)"
        
        if ',y' in operand.lower():
            base = operand.lower().replace(',y', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            
            if (base.startswith('ADDR_') or base.startswith('DATA_') or 
                base.startswith('FUNC_') or base.startswith('0x')):
                return f"M({base} + y)"
            else:
                addr = self.convert_address(base)
                return f"M({addr} + y)"
        
        # Indirect addressing
        if operand.startswith('(') and operand.endswith(')'):
            inner = operand[1:-1]
            if (inner.startswith('ADDR_') or inner.startswith('DATA_') or 
                inner.startswith('FUNC_') or inner.startswith('0x')):
                return f"W({inner})"
            else:
                addr = self.convert_address(inner)
                return f"W({addr})"
        
        # Direct addressing
        if (operand.startswith('ADDR_') or operand.startswith('DATA_') or 
            operand.startswith('FUNC_') or operand.startswith('0x')):
            return f"M({operand})"
        else:
            addr = self.convert_address(operand)
            return f"M({addr})"
    
    def write_address(self, operand):
        """Convert operand for writing"""
        if not operand:
            return "0"
        
        operand = operand.strip()
        
        if ',x' in operand.lower():
            base = operand.lower().replace(',x', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            
            if (base.startswith('ADDR_') or base.startswith('DATA_') or 
                base.startswith('FUNC_') or base.startswith('0x')):
                return f"{base} + x"
            else:
                addr = self.convert_address(base)
                return f"{addr} + x"
        
        if ',y' in operand.lower():
            base = operand.lower().replace(',y', '').strip()
            if base.startswith('(') and base.endswith(')'):
                base = base[1:-1]
            
            if (base.startswith('ADDR_') or base.startswith('DATA_') or 
                base.startswith('FUNC_') or base.startswith('0x')):
                return f"{base} + y"
            else:
                addr = self.convert_address(base)
                return f"{addr} + y"
        
        # Direct addressing
        if (operand.startswith('ADDR_') or operand.startswith('DATA_') or 
            operand.startswith('FUNC_') or operand.startswith('0x')):
            return operand
        else:
            return self.convert_address(operand)
    
    def convert_address(self, addr):
        """Convert address to C++ format"""
        addr = addr.strip()
        
        # Remove addressing prefixes
        if addr.startswith('a:') or addr.startswith('z:'):
            addr = addr[2:]
        
        # Direct hex
        if addr.startswith("\'"):
            hex_part = addr[1:].upper()
            if all(c in '0123456789ABCDEF' for c in hex_part):
                if len(hex_part) == 4:
                    return f"ADDR_{hex_part}"
                else:
                    return f"0x{hex_part}"
            return "0"
        
        # Hardware registers
        hw_regs = {
            'PPU_STATUS': 'PPU_STATUS', 'PPU_CTRL': 'PPU_CTRL', 'PPU_MASK': 'PPU_MASK',
            'PPU_SCROLL': 'PPU_SCROLL', 'PPU_ADDR': 'PPU_ADDR', 'PPU_DATA': 'PPU_DATA',
            'APU_SND_CHN': 'APU_SND_CHN', 'OAM_ADDR': 'OAM_ADDR', 'OAM_DMA': 'OAM_DMA',
            'JOYPAD1': 'JOYPAD1', 'JOYPAD2': 'JOYPAD2'
        }
        
        if addr.upper() in hw_regs:
            return hw_regs[addr.upper()]
        
        # Symbol lookup
        if addr in self.symbols:
            return self.symbols[addr]
        
        # Invalid identifier patterns
        if addr.startswith('_'):
            # data pattern
            data_match = re.match(r'_data_([0-9a-fA-F]{4})', addr, re.IGNORECASE)
            if data_match:
                return f"DATA_{data_match.group(1).upper()}"
            
            # func pattern
            func_match = re.match(r'_func_([0-9a-fA-F]{4})', addr, re.IGNORECASE)
            if func_match:
                return f"FUNC_{func_match.group(1).upper()}"
            
            # Generic patterns
            patterns = [
                r'_(?:var|data)_([0-9a-fA-F]{4})',
                r'_([0-9a-fA-F]{4})_',
                r'_([0-9a-fA-F]{4})$'
            ]
            
            for pattern in patterns:
                match = re.search(pattern, addr, re.IGNORECASE)
                if match:
                    return f"ADDR_{match.group(1).upper()}"
        
        # Plain hex
        if len(addr) == 4 and all(c in '0123456789ABCDEFabcdef' for c in addr):
            return f"ADDR_{addr.upper()}"
        
        # Validate identifier
        if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', addr):
            # Extract hex from invalid identifier
            hex_match = re.search(r'([0-9a-fA-F]{4})', addr, re.IGNORECASE)
            if hex_match:
                return f"ADDR_{hex_match.group(1).upper()}"
            else:
                return "0"
        
        return addr
    
    def save_output(self, output_dir):
        """Save all generated files"""
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        
        # Save all files
        files = [
            ("SMB.cpp", self.source_output),
            ("SMBData.cpp", self.data_output),
            ("SMBDataPointers.hpp", self.data_header_output),
            ("SMBConstants.hpp", self.constants_header_output)
        ]
        
        for filename, content in files:
            file_path = output_path / filename
            with open(file_path, 'w') as f:
                f.write(content)
            print(f"Generated: {file_path}")

def main():
    if len(sys.argv) < 3:
        print("Usage: python enhanced_listing_translator.py <listing_file> <output_dir> [config_dir]")
        print("")
        print("Arguments:")
        print("  listing_file  - CA65 listing file (.lst)")
        print("  output_dir    - Directory for generated C++ files")
        print("  config_dir    - Optional directory with label configuration files")
        print("")
        print("Generated files:")
        print("  SMB.cpp               - Main C++ source code")
        print("  SMBData.cpp           - Data loading implementation")
        print("  SMBDataPointers.hpp   - Data pointer declarations")
        print("  SMBConstants.hpp      - Symbol constants")
        sys.exit(1)
    
    listing_file = sys.argv[1]
    output_dir = sys.argv[2]
    config_dir = sys.argv[3] if len(sys.argv) > 3 else None
    
    if not os.path.exists(listing_file):
        print(f"Error: Listing file '{listing_file}' not found")
        sys.exit(1)
    
    try:
        translator = EnhancedListingTranslator(listing_file, config_dir)
        translator.save_output(output_dir)
        print("\nTranslation completed successfully!")
        print(f"Generated files saved to: {output_dir}")
        
        if config_dir:
            print(f"Using configuration from: {config_dir}")
        else:
            print("\nTo customize label classification, create config files:")
            print("  data_labels.txt  - One label per line for data labels")
            print("  code_labels.txt  - One label per line for code labels")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
