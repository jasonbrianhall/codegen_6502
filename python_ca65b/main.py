import argparse
import sys

SMBCONSTANTS = """#ifndef SMBCONSTANTS_HPP
#define SMBCONSTANTS_HPP
"""

SMB = """#include "SMB.hpp"
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

def process_line(line):
    global SMBCONSTANTS, SMB  # Declare as global to modify them
    
    code = line.split(";")[0]
    try:
        comment = line.split(";")[1]
    except IndexError:  # Be more specific about the exception
        comment = ""
    
    # print("Code: ", code, "\nComment: ", comment, "\n")
    if '=' in code:
        SMBCONSTANTS = SMBCONSTANTS + "#define " + code.replace("$", "0x")
        if not comment == "":
            SMBCONSTANTS += "// " + comment
    else:
        SMB = SMB + code + "\n"

def main():
    global SMBCONSTANTS, SMB
    
    # Set up argument parser
    parser = argparse.ArgumentParser(description='Process lines from a file')
    parser.add_argument('filename', help='Path to the input file')
    parser.add_argument('--encoding', default='utf-8', help='File encoding (default: utf-8)')
    
    # Parse arguments
    args = parser.parse_args()
    
    try:
        # Open and process the file
        with open(args.filename, 'r', encoding=args.encoding) as file:
            for line_number, line in enumerate(file, 1):
                try:
                    process_line(line)
                except Exception as e:
                    print(f"Error processing line {line_number}: {e}", file=sys.stderr)
                    
    except FileNotFoundError:
        print(f"Error: File '{args.filename}' not found.", file=sys.stderr)
        sys.exit(1)
    except PermissionError:
        print(f"Error: Permission denied accessing '{args.filename}'.", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)
    
    # Close the C++ files properly and print both
    SMBCONSTANTS += "\n#endif"
    SMB += "\n}"
    
    print("//=== SMBCONSTANTS.HPP ===")
    print(SMBCONSTANTS)
    #print("\n=== SMB.CPP ===")
    #print(SMB)

if __name__ == "__main__":
    main()
