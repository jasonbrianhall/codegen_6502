#!/usr/bin/env python3
"""
Convert 6502 assembly files to JSON format for easier processing.
"""

import re
import json
import sys
from typing import Dict, List, Any, Optional

class AsmToJsonConverter:
    def __init__(self):
        self.labels = []
        self.declarations = []
        self.current_address = 0x8000
        
    def parse_file(self, filename: str) -> Dict[str, Any]:
        """Parse an ASM file and return JSON structure."""
        result = {
            "labels": [],
            "declarations": [],
            "directives": []
        }
        
        with open(filename, 'r') as f:
            lines = f.readlines()
        
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            line_num = i + 1
            
            # Skip empty lines and comments
            if not line or line.startswith(';'):
                i += 1
                continue
            
            # Extract comment if present
            comment = None
            if ';' in line:
                parts = line.split(';', 1)
                line = parts[0].strip()
                comment = parts[1].strip()
            
            # Check for label
            if line.endswith(':'):
                label_data = self.parse_label(line, lines, i, comment)
                if label_data:
                    result["labels"].append(label_data)
                    # Skip lines that were consumed by parse_label
                    i += label_data.get("lines_consumed", 1)
                else:
                    i += 1
            
            # Check for declaration (NAME = VALUE)
            elif '=' in line and not line.startswith('.'):
                decl = self.parse_declaration(line, comment, line_num)
                if decl:
                    result["declarations"].append(decl)
                i += 1
            
            # Check for directives
            elif line.startswith('.'):
                directive = self.parse_directive(line, comment, line_num)
                if directive:
                    result["directives"].append(directive)
                i += 1
            
            else:
                # Standalone instruction - treat as unlabeled code
                if self.is_instruction(line):
                    inst = self.parse_instruction(line, comment, line_num)
                    if inst:
                        label_data = {
                            "name": f"unlabeled_{line_num:04d}",
                            "type": "code",
                            "address": f"0x{self.current_address:04X}",
                            "line": line_num,
                            "content": [inst]
                        }
                        result["labels"].append(label_data)
                        self.current_address += 3  # Estimate
                i += 1
        
        return result
    
    def parse_label(self, label_line: str, all_lines: List[str], start_idx: int, comment: Optional[str]) -> Optional[Dict[str, Any]]:
        """Parse a label and its following content."""
        label_name = label_line[:-1]  # Remove ':'
        
        label_data = {
            "name": label_name,
            "type": "unknown",
            "address": f"0x{self.current_address:04X}",
            "line": start_idx + 1,
            "content": []
        }
        
        if comment:
            label_data["comment"] = comment
        
        # Look at following lines to determine type and content
        i = start_idx + 1
        lines_consumed = 1
        
        while i < len(all_lines):
            line = all_lines[i].strip()
            
            # Skip empty lines
            if not line:
                i += 1
                lines_consumed += 1
                continue
            
            # Stop at next label
            if line.endswith(':'):
                break
            
            # Extract comment
            line_comment = None
            if ';' in line:
                parts = line.split(';', 1)
                line = parts[0].strip()
                line_comment = parts[1].strip()
            
            if not line:
                i += 1
                lines_consumed += 1
                continue
            
            # Check for data directives
            if line.startswith('.db') or line.startswith('.byte'):
                label_data["type"] = "data"
                data_content = self.parse_data_directive(line, line_comment, i + 1)
                if data_content:
                    label_data["content"].append(data_content)
            
            elif line.startswith('.dw') or line.startswith('.word'):
                label_data["type"] = "data"
                data_content = self.parse_data_directive(line, line_comment, i + 1, word_size=True)
                if data_content:
                    label_data["content"].append(data_content)
            
            # Check for instructions
            elif self.is_instruction(line):
                if label_data["type"] == "unknown":
                    label_data["type"] = "code"
                inst = self.parse_instruction(line, line_comment, i + 1)
                if inst:
                    label_data["content"].append(inst)
            
            # Check for other directives
            elif line.startswith('.'):
                directive = self.parse_directive(line, line_comment, i + 1)
                if directive:
                    label_data["content"].append(directive)
            
            else:
                # Unknown content
                label_data["content"].append({
                    "type": "unknown",
                    "content": line,
                    "line": i + 1,
                    "comment": line_comment
                })
            
            i += 1
            lines_consumed += 1
        
        # Set default type if still unknown
        if label_data["type"] == "unknown":
            label_data["type"] = "code" if label_data["content"] else "empty"
        
        # Estimate address advancement
        if label_data["type"] == "data":
            self.current_address += len(label_data["content"]) * 8  # Rough estimate
        else:
            self.current_address += len(label_data["content"]) * 3  # Rough estimate
        
        label_data["lines_consumed"] = lines_consumed
        return label_data
    
    def parse_declaration(self, line: str, comment: Optional[str], line_num: int) -> Optional[Dict[str, Any]]:
        """Parse a NAME = VALUE declaration."""
        if '=' not in line:
            return None
        
        parts = line.split('=', 1)
        if len(parts) != 2:
            return None
        
        name = parts[0].strip()
        value = parts[1].strip()
        
        decl = {
            "name": name,
            "value": value,
            "line": line_num
        }
        
        if comment:
            decl["comment"] = comment
        
        return decl
    
    def parse_directive(self, line: str, comment: Optional[str], line_num: int) -> Optional[Dict[str, Any]]:
        """Parse a directive like .base, .dsb, etc."""
        parts = line.split(None, 1)
        directive_name = parts[0]
        directive_args = parts[1] if len(parts) > 1 else ""
        
        directive = {
            "type": "directive",
            "name": directive_name,
            "args": directive_args,
            "line": line_num
        }
        
        if comment:
            directive["comment"] = comment
        
        return directive
    
    def parse_data_directive(self, line: str, comment: Optional[str], line_num: int, word_size: bool = False) -> Optional[Dict[str, Any]]:
        """Parse .db or .dw directive."""
        # Remove directive name
        if line.startswith('.db') or line.startswith('.byte'):
            data_part = line[3:].strip()
        elif line.startswith('.dw') or line.startswith('.word'):
            data_part = line[3:].strip()
        else:
            return None
        
        # Parse data values (comma-separated)
        values = []
        if data_part:
            raw_values = data_part.split(',')
            for val in raw_values:
                values.append(val.strip())
        
        data = {
            "type": "data",
            "directive": "word" if word_size else "byte",
            "values": values,
            "line": line_num
        }
        
        if comment:
            data["comment"] = comment
        
        return data
    
    def parse_instruction(self, line: str, comment: Optional[str], line_num: int) -> Optional[Dict[str, Any]]:
        """Parse an assembly instruction."""
        parts = line.split(None, 1)
        if not parts:
            return None
        
        opcode = parts[0].lower()
        operand = parts[1] if len(parts) > 1 else ""
        
        inst = {
            "type": "instruction",
            "opcode": opcode,
            "operand": operand,
            "line": line_num
        }
        
        if comment:
            inst["comment"] = comment
        
        return inst
    
    def is_instruction(self, line: str) -> bool:
        """Check if a line contains an assembly instruction."""
        if not line or line.startswith('.') or '=' in line:
            return False
        
        # List of common 6502 instructions
        instructions = {
            'lda', 'ldx', 'ldy', 'sta', 'stx', 'sty',
            'tax', 'tay', 'txa', 'tya', 'tsx', 'txs',
            'pha', 'php', 'pla', 'plp',
            'and', 'eor', 'ora', 'bit',
            'adc', 'sbc', 'cmp', 'cpx', 'cpy',
            'inc', 'inx', 'iny', 'dec', 'dex', 'dey',
            'asl', 'lsr', 'rol', 'ror',
            'jmp', 'jsr', 'rts', 'rti',
            'bcc', 'bcs', 'beq', 'bmi', 'bne', 'bpl', 'bvc', 'bvs',
            'clc', 'cld', 'cli', 'clv', 'sec', 'sed', 'sei',
            'brk', 'nop',
            # Undocumented instructions
            'slo', 'dcp', 'isc', 'rla', 'sre', 'lax'
        }
        
        parts = line.split()
        if parts:
            opcode = parts[0].lower()
            return opcode in instructions
        
        return False

def main():
    if len(sys.argv) != 3:
        print("Usage: python asm_to_json.py <input.asm> <output.json>")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    converter = AsmToJsonConverter()
    
    try:
        result = converter.parse_file(input_file)
        
        with open(output_file, 'w') as f:
            json.dump(result, f, indent=2)
        
        print(f"Converted {input_file} to {output_file}")
        print(f"Found {len(result['labels'])} labels, {len(result['declarations'])} declarations, {len(result['directives'])} directives")
        
        # Print some stats
        data_labels = sum(1 for label in result['labels'] if label['type'] == 'data')
        code_labels = sum(1 for label in result['labels'] if label['type'] == 'code')
        print(f"Data labels: {data_labels}, Code labels: {code_labels}")
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
