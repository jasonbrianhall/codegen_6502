#!/usr/bin/env python3
"""
6502 Assembly Code Generator - FIXED Main Application with Debug Parser

Converts 6502 assembly code to C++ code for game engines.
This is the FIXED version that addresses section skipping issues.

Usage: python main.py <INPUT_ASM_FILE> <OUTPUT_DIRECTORY>
"""

import sys
import os
from pathlib import Path

from lexer import Lexer
from parser import Parser  # This will use the fixed parser
from ast_nodes import cleanup_ast, validate_ast_integrity, print_node
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

def debug_print_ast_summary(root, source_lines=None):
    """Print a comprehensive AST summary"""
    print(f"\n{'='*60}")
    print("AST STRUCTURE SUMMARY")
    print(f"{'='*60}")
    
    labels = []
    declarations = []
    other_nodes = []
    
    for i, child in enumerate(root.children):
        if child.type.name == 'AST_LABEL':
            labels.append((i, child.value, child.line_number))
        elif child.type.name == 'AST_DECL':
            declarations.append((i, child.value))
        else:
            other_nodes.append((i, child.type.name))
    
    print(f"Total root children: {len(root.children)}")
    print(f"  Labels: {len(labels)}")
    print(f"  Declarations: {len(declarations)}")
    print(f"  Other: {len(other_nodes)}")
    
    if labels:
        print(f"\nLABELS FOUND:")
        for i, (idx, name, line) in enumerate(labels):
            print(f"  [{idx:3d}] {name:20s} (line {line:4d})")
            if i >= 20:  # Limit output
                print(f"  ... and {len(labels) - 20} more labels")
                break
    
    if declarations:
        print(f"\nDECLARATIONS:")
        for idx, name in declarations[:10]:  # Show first 10
            print(f"  [{idx:3d}] {name}")
        if len(declarations) > 10:
            print(f"  ... and {len(declarations) - 10} more declarations")
    
    print(f"{'='*60}\n")
    
    # Validate integrity
    validate_ast_integrity(root, source_lines)

def main():
    """FIXED main function with comprehensive debugging"""
    if len(sys.argv) < 3:
        print("usage: python main.py <INPUT ASM FILE> <OUTPUT DIRECTORY> [CONFIG DIRECTORY] [-ca65] [-debug] [-ast]")
        print("  -ca65: Use CA65 assembly format instead of original format")
        print("  -debug: Enable detailed debug output from parser")
        print("  -ast: Print detailed AST structure")
        print("Examples:")
        print("  python main.py game.asm output_dir")
        print("  python main.py game.asm output_dir -ca65 -debug")
        print("  python main.py game.asm output_dir my_config -ca65 -debug -ast")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_dir = sys.argv[2]
    
    # Parse optional arguments
    config_dir = None
    is_ca65 = False
    debug_mode = False
    show_ast = False
    
    # Check all remaining arguments
    for i in range(3, len(sys.argv)):
        arg = sys.argv[i]
        if arg == "-ca65":
            is_ca65 = True
        elif arg == "-debug":
            debug_mode = True
        elif arg == "-ast":
            show_ast = True
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
        
        print(f"Processing: {input_file}")
        print(f"Debug mode: {'ON' if debug_mode else 'OFF'}")
        print(f"AST display: {'ON' if show_ast else 'OFF'}")
        print(f"Format: {'CA65' if is_ca65 else 'Original'}")
        
        # Split source into lines for debugging
        source_lines = input_text.split('\n')
        print(f"Source file has {len(source_lines)} lines")
        
        # Show some sample lines with labels for verification
        print("\nSample labels from source:")
        import re
        label_count = 0
        for line_num, line in enumerate(source_lines[:200], 1):  # Check first 200 lines
            if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*:', line.strip()):
                print(f"  Line {line_num:4d}: {line.strip()}")
                label_count += 1
                if label_count >= 10:  # Show first 10 labels
                    break
        
        # Lexical analysis
        print(f"\n{'='*60}")
        print("LEXICAL ANALYSIS")
        print(f"{'='*60}")
        
        lexer = Lexer(input_text)
        tokens = lexer.tokenize()
        print(f"Generated {len(tokens)} tokens")
        
        # Count LABEL tokens specifically
        label_tokens = [t for t in tokens if t.type.name == 'LABEL']
        print(f"Found {len(label_tokens)} LABEL tokens")
        
        if debug_mode and label_tokens:
            print("First 10 LABEL tokens:")
            for i, token in enumerate(label_tokens[:10]):
                print(f"  [{i:2d}] LABEL: '{token.value}' (line {token.line})")
        
        # Parsing with FIXED parser
        print(f"\n{'='*60}")
        print("PARSING WITH FIXED PARSER")
        print(f"{'='*60}")
        
        parser = Parser(tokens)
        parser.debug_mode = debug_mode
        parser.set_source_lines(source_lines)
        
        # Parse with comprehensive error recovery
        try:
            ast_root = parser.parse()
            print(f"✓ Parsing completed successfully")
            print(f"  Generated {len(ast_root.children)} top-level AST nodes")
        except Exception as e:
            print(f"✗ Parser error: {e}")
            if debug_mode:
                import traceback
                traceback.print_exc()
            
            # This shouldn't happen with the fixed parser, but just in case
            print("✗ Could not recover from parser error")
            sys.exit(1)
        
        # AST cleanup with debugging
        print(f"\n{'='*60}")
        print("AST CLEANUP")
        print(f"{'='*60}")
        
        cleanup_ast(ast_root, debug=debug_mode)
        print("✓ AST cleanup completed")
        
        # Display AST summary
        debug_print_ast_summary(ast_root, source_lines)
        
        # Show detailed AST structure if requested
        if show_ast:
            print(f"\n{'='*60}")
            print("DETAILED AST STRUCTURE")
            print(f"{'='*60}")
            # Only show first few nodes to avoid overwhelming output
            print("First 5 AST nodes:")
            for i, child in enumerate(ast_root.children[:5]):
                print(f"\n--- Node {i} ---")
                print_node(child)
            
            if len(ast_root.children) > 5:
                print(f"\n... and {len(ast_root.children) - 5} more nodes")
            print(f"{'='*60}\n")
        
        # Translation
        print(f"{'='*60}")
        print("TRANSLATION")
        print(f"{'='*60}")
        
        if config_dir:
            print(f"Using config directory: {config_dir}")
        
        # Pass is_ca65 flag to translator
        translator = Translator(input_file, ast_root, config_dir, is_ca65)
        print("✓ Translation completed")
        
        # Create output directory and write files
        print(f"\n{'='*60}")
        print("OUTPUT GENERATION")
        print(f"{'='*60}")
        
        create_output_directory(output_dir)
        write_output_files(translator, output_dir)
        
        print(f"\n✅ SUCCESS: Translation completed successfully!")
        print(f"   Output files written to: {output_dir}")
        
        if config_dir:
            analyzer_script = "ca65_analyzer.py" if is_ca65 else "rom_analyzer.py"
            print(f"\n💡 If you encounter indirect jump errors, run:")
            print(f"   python {analyzer_script} {input_file}")
            print(f"   Then edit the files in {config_dir}/")
        
        # Final statistics
        print(f"\n📊 FINAL STATISTICS:")
        print(f"   Source lines: {len(source_lines)}")
        print(f"   Tokens generated: {len(tokens)}")
        print(f"   LABEL tokens: {len(label_tokens)}")
        print(f"   AST root children: {len(ast_root.children)}")
        
        # Count different types of AST nodes
        label_nodes = [c for c in ast_root.children if c.type.name == 'AST_LABEL']
        decl_nodes = [c for c in ast_root.children if c.type.name == 'AST_DECL']
        
        print(f"   Labels in AST: {len(label_nodes)}")
        print(f"   Declarations in AST: {len(decl_nodes)}")
        
        if len(label_tokens) != len(label_nodes):
            print(f"   ⚠️  WARNING: Token/AST label count mismatch!")
            print(f"   This indicates some labels may have been lost during parsing.")
        else:
            print(f"   ✅ Label token/AST count matches!")
        
    except Exception as e:
        print(f"\n❌ FATAL ERROR: {e}")
        if debug_mode:
            import traceback
            traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
