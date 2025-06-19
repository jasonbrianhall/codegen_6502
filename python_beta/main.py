#!/usr/bin/env python3
"""
6502 Assembly Code Generator - Main Application

Converts 6502 assembly code to C++ code for game engines.
This is a Python port of the original C++ version.

Usage: python main.py <INPUT_ASM_FILE> <OUTPUT_DIRECTORY>
"""

import sys
import os
from pathlib import Path

from lexer import Lexer
from parser import Parser
from ast_nodes import cleanup_ast
from translator import Translator
from util import clear_comments

def create_output_directory(output_dir: str):
    """Create output directory if it doesn't exist"""
    Path(output_dir).mkdir(parents=True, exist_ok=True)

def write_output_files(translator: Translator, output_dir: str):
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
    """Main function"""
    if len(sys.argv) < 3:
        print("usage: python main.py <INPUT ASM FILE> <OUTPUT DIRECTORY> [CONFIG DIRECTORY]")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_dir = sys.argv[2]
    config_dir = sys.argv[3] if len(sys.argv) > 3 else None
    
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
        
        # Lexical analysis
        print("Performing lexical analysis...")
        lexer = Lexer(input_text)
        tokens = lexer.tokenize()
        print(f"Generated {len(tokens)} tokens")
        
        # Parsing
        print("Parsing...")
        parser = Parser(tokens)
        ast_root = parser.parse()
        print(f"Parsed {len(ast_root.children)} top-level nodes")
        
        # Cleanup AST (reverse lists, etc.)
        print("Cleaning up AST...")
        cleanup_ast(ast_root)
        
        # Translation
        print("Translating to C++...")
        if config_dir:
            print(f"Using config directory: {config_dir}")
        translator = Translator(input_file, ast_root, config_dir)
        
        # Create output directory
        create_output_directory(output_dir)
        
        # Write output files
        write_output_files(translator, output_dir)
        
        print("Translation completed successfully!")
        if config_dir:
            print(f"\nIf you encounter label classification errors, edit the files in {config_dir}:")
            print("  - data_labels.txt (for labels that should generate data pointers)")
            print("  - code_labels.txt (for labels used in goto statements)")
            print("  - alias_labels.txt (for simple label aliases)")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
