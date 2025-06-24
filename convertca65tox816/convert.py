#!/usr/bin/env python3
"""
X816 Compatible CA65 to X816 Assembly Converter
Fixes naming and syntax issues for x816 compatibility
Adds forward declarations for single-pass assembly
"""

import re
import sys
import os
import argparse

class CA65ToX816Converter:
    def __init__(self):
        self.conversions = []
        self.warnings = []
        self.functions = {}  # Track function definitions and calls

    def clean_identifier(self, name):
        """Clean up identifier names for x816 compatibility"""
        # Remove problematic prefixes and characters
        name = re.sub(r'^_+', '', name)  # Remove leading underscores
        name = re.sub(r'_indexed$', '', name)  # Remove _indexed suffix
        name = re.sub(r'_var_', 'v', name)  # Simplify variable names
        name = re.sub(r'_data_', 'd', name)  # Simplify data names
        name = re.sub(r'_label_', 'L', name)  # Simplify labels
        name = re.sub(r'_func_', 'F', name)  # Simplify function names
        
        # Ensure it starts with a letter
        if name and name[0].isdigit():
            name = 'N' + name
            
        return name

    def find_functions_and_labels(self, content):
        """First pass: find all function/label definitions and calls"""
        lines = content.split('\n')
        
        for i, line in enumerate(lines):
            stripped = line.strip()
            
            # Skip comments and empty lines
            if not stripped or stripped.startswith(';'):
                continue
            
            # Find function/label definitions (labels ending with colon)
            label_match = re.match(r'^([a-zA-Z_][a-zA-Z0-9_]*):?$', stripped)
            if label_match:
                label_name = label_match.group(1)
                # Extract address from comment if present
                comment_match = re.search(r';\s*\$([0-9A-Fa-f]+)', line)
                if comment_match:
                    address = '$' + comment_match.group(1).upper()
                    self.functions[label_name] = address
            
            # Find JSR/JMP calls to functions
            jsr_match = re.search(r'(jsr|jmp)\s+([a-zA-Z_][a-zA-Z0-9_]*)', line, re.IGNORECASE)
            if jsr_match:
                func_name = jsr_match.group(2)
                if func_name not in self.functions:
                    self.functions[func_name] = None  # Mark as needed but address unknown

    def convert(self, content: str) -> str:
        """Main conversion function"""
        # First pass: collect function information
        self.find_functions_and_labels(content)
        
        lines = content.split('\n')
        skip_header = False
        output_lines = []
        
        # Add x816 directives at the start
        output_lines.extend([
            ';-------------------------------------------------------------------------------------',
            ';DIRECTIVES',
            '',
            '       .index 8',
            '       .mem 8',
            '',
            ';-------------------------------------------------------------------------------------',
            ''
        ])
        
        # Add forward declarations for functions with known addresses
        if self.functions:
            output_lines.append(';-------------------------------------------------------------------------------------')
            output_lines.append(';FORWARD DECLARATIONS')
            output_lines.append('')
            
            for func_name, address in sorted(self.functions.items()):
                if address and func_name.startswith(('func_', 'label_')):
                    clean_name = self.clean_identifier(func_name)
                    output_lines.append(f'{clean_name} .equ {address}')
            
            output_lines.extend(['', ';-------------------------------------------------------------------------------------', ''])
        
        for i, line in enumerate(lines):
            original_line = line
            stripped = line.strip()
            
            # Skip empty lines and comments
            if not stripped or stripped.startswith(';'):
                output_lines.append(line)
                continue
            
            # Detect and skip header section
            if '.org $0000' in line and i < 100:
                output_lines.append('; NES HEADER SECTION REMOVED - add manually')
                skip_header = True
                continue
            
            if skip_header:
                if ('.db' in line and ('NES' in line or '$1a' in line)) or \
                   'Magic string' in line or \
                   'Number of' in line or \
                   'Control bits' in line or \
                   'banks' in line:
                    output_lines.append('; ' + line)
                    continue
                elif '.org' in line and '$0000' not in line:
                    skip_header = False
                elif stripped and not any(x in line for x in ['.db', 'Magic', 'Number', 'Control', 'banks']):
                    skip_header = False
            
            # Convert segments to .org
            if '.segment' in line:
                if '"CODE"' in line or "'CODE'" in line:
                    line = '.org $C000'
            
            # Convert data directives
            line = re.sub(r'\.byte\b', '.db', line)
            line = re.sub(r'\.word\b', '.dw', line)
            line = re.sub(r'\.dbyt\b', '.dw', line)
            line = re.sub(r'\.dword\b', '.dd', line)
            line = re.sub(r'\.addr\b', '.dw', line)
            
            # Convert storage directives
            line = re.sub(r'\.res\s+(\d+)', r'.ds \1', line)
            
            # Remove .proc/.endproc
            if '.proc' in line or '.endproc' in line:
                line = '; ' + line
            
            # Convert other directives
            line = re.sub(r'\.export\s+(\w+)', r'; .export \1', line)
            line = re.sub(r'\.import\s+(\w+)', r'; .import \1', line)
            line = re.sub(r'\.importzp\s+(\w+)', r'; .importzp \1', line)
            line = re.sub(r'\.exportzp\s+(\w+)', r'; .exportzp \1', line)
            line = re.sub(r'\.setcpu\s+"[^"]*"', r'; setcpu removed (x816 incompatible)', line)
            line = re.sub(r'\.setcpu\s+\S+', r'; setcpu removed (x816 incompatible)', line)
            
            # Clean up variable/label names
            def replace_identifier(match):
                full_match = match.group(0)
                identifier = match.group(1)
                clean_id = self.clean_identifier(identifier)
                return full_match.replace(identifier, clean_id)
            
            # Fix variable assignments
            line = re.sub(r'([_a-zA-Z][_a-zA-Z0-9]*)\s*=', lambda m: self.clean_identifier(m.group(1)) + ' =', line)
            
            # Fix labels
            line = re.sub(r'^([_a-zA-Z][_a-zA-Z0-9]*):?$', lambda m: self.clean_identifier(m.group(1)) + ':', line)
            
            # Fix addressing modes - remove 'a:' and 'z:' prefixes
            line = re.sub(r'\ba:', '', line)
            line = re.sub(r'\bz:', '', line)
            
            # Fix variable references in instructions
            line = re.sub(r'([_a-zA-Z][_a-zA-Z0-9]*)', lambda m: self.clean_identifier(m.group(1)) if m.group(1).startswith('_') else m.group(1), line)
            
            # Track conversions
            if line != original_line:
                self.conversions.append(f"Line {i + 1}: CLEANED IDENTIFIERS")
            
            output_lines.append(line)
        
        return '\n'.join(output_lines)

    def generate_instructions(self, filename: str, input_file: str, output_file: str):
        """Generate build instructions"""
        instructions = f"""# Build Instructions for {output_file}

## Step 1: Assemble with x816
```bash
x816 {output_file}
```
This creates {output_file.replace('.asm', '.bin')}

## Step 2: Create NES header (if needed)
```bash
printf "4E 45 53 1A 02 01 01 00 00 00 00 00 00 00 00 00" | xxd -r -p > header.bin
```

## Step 3: Extract CHR data from original ROM (if needed)
```bash
tail -c 8192 original.nes > graphics.chr
```

## Step 4: Combine into final ROM (if needed)
```bash
cat header.bin {output_file.replace('.asm', '.bin')} graphics.chr > final.nes
```

## Test
```bash
fceux final.nes
```

## Notes
- All variable names were cleaned for x816 compatibility
- Header and CHR segments were removed
- Addressing mode prefixes (a:, z:) were removed
- Forward declarations added for single-pass assembly
- The x816 assembler will only generate the PRG ROM portion
"""
        
        with open(filename, 'w') as f:
            f.write(instructions)

def main():
    parser = argparse.ArgumentParser(description='Convert ca65 assembly files to x816 format')
    parser.add_argument('input_file', help='Input ca65 assembly file')
    parser.add_argument('output_file', help='Output x816 assembly file')
    parser.add_argument('--verbose', '-v', action='store_true', help='Show detailed conversion information')
    
    args = parser.parse_args()
    
    # Check if output file exists
    if os.path.exists(args.output_file):
        response = input(f"Output file '{args.output_file}' exists. Overwrite? (y/N): ")
        if response.lower() != 'y':
            print("Conversion cancelled.")
            sys.exit(1)
    
    # Read input file
    try:
        with open(args.input_file, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading input file: {e}")
        sys.exit(1)
    
    print(f"Converting {args.input_file}...")
    
    # Convert the file
    converter = CA65ToX816Converter()
    converted = converter.convert(content)
    
    # Write output file
    try:
        with open(args.output_file, 'w', encoding='utf-8', newline='\r\n') as f:
            f.write(converted)
        print(f"Conversion complete: {args.output_file}")
        print(f"Made {len(converter.conversions)} conversions")
        
        if converter.functions:
            print(f"Added forward declarations for {len([f for f in converter.functions.values() if f])} functions")
        
    except Exception as e:
        print(f"Error writing output file: {e}")
        sys.exit(1)
    
    # Generate instructions file
    base_name = os.path.splitext(args.output_file)[0]
    instructions_file = f"{base_name}_instructions.txt"
    
    try:
        converter.generate_instructions(instructions_file, args.input_file, args.output_file)
        print(f"Instructions created: {instructions_file}")
    except Exception as e:
        print(f"Could not create instructions file: {e}")

if __name__ == "__main__":
    main()
