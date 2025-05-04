#!/usr/bin/env python3
"""
Python implementation of the 6502 assembler and C++ code generator
Main program entry point
"""

import os
import sys
from asm6502_lexer import lexer
from asm6502_parser import parse
from translator import Translator
from ast_classes import cleanup_ast, print_node

def main():
    """
    Main program entry point
    """
    if len(sys.argv) < 3:
        print("usage: codegen.py <INPUT ASM FILE> <OUTPUT ROOT DIRECTORY>")
        sys.exit(1)
        
    # Parse the input file
    try:
        with open(sys.argv[1], 'r') as f:
            data = f.read()
            
        # Parse the ASM file
        root = parse(data)
        
        # For debugging: uncomment to print the AST
        # for node in root.children:
        #     print_node(node)
            
        # Create translator
        translator = Translator(sys.argv[1], root)
        
        # Get the output directory
        output_dir = sys.argv[2]
        
        # Create output directories if they don't exist
        os.makedirs(os.path.join(output_dir, "source/SMB"), exist_ok=True)
        
        # Write the output files
        source_file_path = os.path.join(output_dir, "source/SMB/SMB.cpp")
        with open(source_file_path, 'w') as f:
            f.write(translator.get_source_output())
            
        data_file_path = os.path.join(output_dir, "source/SMB/SMBData.cpp")
        with open(data_file_path, 'w') as f:
            f.write(translator.get_data_output())
            
        data_header_file_path = os.path.join(output_dir, "source/SMB/SMBDataPointers.hpp")
        with open(data_header_file_path, 'w') as f:
            f.write(translator.get_data_header_output())
            
        constant_header_file_path = os.path.join(output_dir, "source/SMB/SMBConstants.hpp")
        with open(constant_header_file_path, 'w') as f:
            f.write(translator.get_constant_header_output())
            
        print(f"Generated C++ files in {output_dir}/source/SMB/")
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
        
if __name__ == "__main__":
    main()
