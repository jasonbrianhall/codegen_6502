#!/usr/bin/env python3
"""
6502 Assembly Code Generator - Main Application with Debug Parser

Converts 6502 assembly code to C++ code for game engines.
This is a Python port of the original C++ version.

Usage: python main.py <INPUT_ASM_FILE> <OUTPUT_DIRECTORY>
"""

import sys
import os
from pathlib import Path

from lexer import Lexer
from parser import Parser  # This will use your debug parser
from ast_nodes import cleanup_ast
from util import clear_comments
from translator import Translator

# Enhanced Translator class with variable detection
class EnhancedTranslator:
    def __init__(self, input_filename: str, ast_root_node, config_dir: str = None, is_ca65: bool = False):
        self.input_filename = input_filename
        self.root = ast_root_node
        self.return_label_index = 0
        self.skip_next_instruction = False
        self.skip_next_instruction_index = 0
        self.config_dir = config_dir
        self.is_ca65 = is_ca65
        
        # Detect missing variables from source
        self.missing_variables = self.detect_missing_variables()
        
        # Import the original Translator functionality
        from translator import Translator
        self.original_translator = Translator(input_filename, ast_root_node, config_dir, is_ca65)
    
    def detect_missing_variables(self):
        """Detect missing variables from assembly source"""
        missing_vars = {}
        
        try:
            with open(self.input_filename, 'r') as f:
                content = f.read()
            
            # Find all variable usage patterns
            import re
            
            # Pattern for variables used but not declared
            used_vars = set()
            declared_vars = set()
            
            # Find declarations (name = $address)
            decl_pattern = re.compile(r'^([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*\$([0-9A-Fa-f]+)', re.MULTILINE)
            for match in decl_pattern.finditer(content):
                declared_vars.add(match.group(1))
            
            # Find usage patterns
            usage_patterns = [
                r'[za]:(_var_[0-9A-Fa-f]+)',  # CA65 addressing modes
                r'\b(_var_[0-9A-Fa-f]+)\b',   # Direct variable references
                r'\b(_data_[0-9A-Fa-f]+)\b',  # Data references
            ]
            
            for pattern in usage_patterns:
                matches = re.findall(pattern, content)
                used_vars.update(matches)
            
            # Find missing variables
            missing = used_vars - declared_vars
            
            for var in missing:
                # Extract address from variable name
                addr_match = re.search(r'_([0-9A-Fa-f]+)', var)
                if addr_match:
                    missing_vars[var] = addr_match.group(1).upper()
                else:
                    missing_vars[var] = "0000"
            
            if missing_vars:
                print(f"Auto-detected {len(missing_vars)} missing variables:")
                for var, addr in missing_vars.items():
                    print(f"  {var} = $0x{addr}")
                    
        except Exception as e:
            print(f"Warning: Could not detect missing variables: {e}")
        
        return missing_vars
    
    def get_source_output(self):
        output = self.original_translator.get_source_output()
        
        # Fix common issues in the output
        lines = output.split('\n')
        fixed_lines = []
        seen_labels = set()
        
        for line in lines:
            # Skip duplicate labels
            if ':' in line and not line.strip().startswith('//') and not 'case' in line:
                label_name = line.split(':')[0].strip()
                if label_name in seen_labels and not label_name.startswith('Return_'):
                    print(f"Skipping duplicate label: {label_name}")
                    continue
                seen_labels.add(label_name)
            
            # Fix addressing mode references
            if 'z:' in line:
                line = line.replace('z:', '')
            if 'a:' in line:
                line = line.replace('a:', '')
            
            fixed_lines.append(line)
        
        return '\n'.join(fixed_lines)
    
    def get_constant_header_output(self):
        output = self.original_translator.get_constant_header_output()
        
        # Add missing variables to the header
        if self.missing_variables:
            lines = output.split('\n')
            
            # Find the insertion point (after existing #defines, before #endif)
            insert_index = -2  # Before the last two lines (#endif)
            for i, line in enumerate(lines):
                if line.strip().startswith('#define') and i > insert_index:
                    insert_index = i + 1
            
            # Insert missing variables
            missing_defines = []
            missing_defines.append("// Missing variables auto-detected:")
            for var, addr in sorted(self.missing_variables.items()):
                missing_defines.append(f"#define {var} 0x{addr}")
            missing_defines.append("")
            
            # Insert at the right position
            lines[insert_index:insert_index] = missing_defines
            output = '\n'.join(lines)
        
        return output
    
    def get_data_output(self):
        return self.original_translator.get_data_output()
    
    def get_data_header_output(self):
        return self.original_translator.get_data_header_output()

def create_output_directory(output_dir: str):
    """Create output directory if it doesn't exist"""
    Path(output_dir).mkdir(parents=True, exist_ok=True)

def write_output_files(translator, output_dir: str):
    """Write all generated files to the output directory"""
    output_path = Path(output_dir)
    
    # Write source file
    source_file = output_path / "SMB.cpp"
    with open(source_file, 'w') as f:
        f.write(translator.get_source_output())
    
    # Write data file
    data_file = output_path / "SMBData.cpp"
    with open(data_file, 'w') as f:
        f.write(translator.get_data_output())
    
    # Write data header file
    data_header_file = output_path / "SMBDataPointers.hpp"
    with open(data_header_file, 'w') as f:
        f.write(translator.get_data_header_output())
    
    # Write constants header file
    constants_header_file = output_path / "SMBConstants.hpp"
    with open(constants_header_file, 'w') as f:
        f.write(translator.get_constant_header_output())
    
    print(f"Generated files in {output_dir}:")
    print("  SMB.cpp")
    print("  SMBData.cpp")
    print("  SMBDataPointers.hpp")
    print("  SMBConstants.hpp")

def main():
    """Main function with CA65 support and debug parser"""
    if len(sys.argv) < 3:
        print("usage: python main.py <INPUT ASM FILE> <OUTPUT DIRECTORY> [CONFIG DIRECTORY] [-ca65] [-debug]")
        print("  -ca65: Use CA65 assembly format instead of original format")
        print("  -debug: Enable detailed debug output from parser")
        print("Examples:")
        print("  python main.py game.asm output_dir")
        print("  python main.py game.asm output_dir -ca65")
        print("  python main.py game.asm output_dir my_config -ca65 -debug")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_dir = sys.argv[2]
    
    # Parse optional arguments
    config_dir = None
    is_ca65 = False
    debug_mode = False
    
    # Check all remaining arguments
    for i in range(3, len(sys.argv)):
        arg = sys.argv[i]
        if arg == "-ca65":
            is_ca65 = True
        elif arg == "-debug":
            debug_mode = True
        elif not arg.startswith('-'):
            config_dir = arg
    
    # Set default config directory based on format
    if config_dir is None:
        config_dir = "ca65_indirect_config" if is_ca65 else "indirect_jump_config"
    
    # Check if input file exists
    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found")
        sys.exit(1)
    
    try:
        # Clear any previous state
        clear_comments()
        
        # Read input file
        with open(input_file, 'r') as f:
            input_text = f.read()
        
        print(f"Debug mode: {'ON' if debug_mode else 'OFF'}")
        
        # Lexical analysis
        print(f"Performing lexical analysis ({'CA65' if is_ca65 else 'Original'} format)...")
        lexer = Lexer(input_text)
        tokens = lexer.tokenize()
        print(f"Generated {len(tokens)} tokens")
        
        # Show first few tokens in debug mode
        if debug_mode:
            print(f"\nFirst 10 tokens:")
            for i, token in enumerate(tokens[:10]):
                print(f"  [{i}] {token.type.name}: '{token.value}' (line {token.line})")
            print()
        
        # Parsing with debug support
        print("Parsing...")
        parser = Parser(tokens)
        
        # Set debug mode
        parser.debug_mode = debug_mode
        
        # Provide source lines for better debugging
        source_lines = input_text.split('\n')
        parser.set_source_lines(source_lines)
        
        # Parse with error recovery
        try:
            ast_root = parser.parse()
            print(f"Parsed {len(ast_root.children)} top-level nodes")
        except Exception as e:
            print(f"Parser error: {e}")
            if debug_mode:
                import traceback
                traceback.print_exc()
            
            # Try to continue with partial AST if available
            if hasattr(parser, 'root') and parser.root:
                ast_root = parser.root
                print(f"Using partial AST with {len(ast_root.children)} nodes")
            else:
                print("Could not recover from parser error")
                sys.exit(1)
        
        # Cleanup AST (reverse lists, etc.)
        print("Cleaning up AST...")
        cleanup_ast(ast_root)
        
        # Translation
        print("Translating to C++...")
        if config_dir:
            print(f"Using config directory: {config_dir}")
        
        # Use enhanced translator
        #translator = EnhancedTranslator(input_file, ast_root, config_dir, is_ca65)

        translator = Translator(input_file, ast_root, config_dir, is_ca65)        

        # Create output directory
        create_output_directory(output_dir)
        
        # Write output files
        write_output_files(translator, output_dir)
        
        print("Translation completed successfully!")
        if config_dir:
            analyzer_script = "ca65_analyzer.py" if is_ca65 else "rom_analyzer.py"
            print(f"\nIf you encounter indirect jump errors, run: python {analyzer_script} {input_file}")
            print(f"Then edit the files in {config_dir}:")
            print("  - *_targets.txt (for indirect jump targets)")
            if not is_ca65:
                print("  - data_labels.txt (for labels that should generate data pointers)")
                print("  - code_labels.txt (for labels used in goto statements)")
                print("  - alias_labels.txt (for simple label aliases)")
        
    except Exception as e:
        print(f"Error: {e}")
        if debug_mode:
            import traceback
            traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
