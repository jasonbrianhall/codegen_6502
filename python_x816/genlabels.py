#!/usr/bin/env python3
"""
6502 Assembly Label Analyzer
Analyzes assembly code and creates configuration files for label classification
"""

import sys
import os
import re
from pathlib import Path
from typing import Dict, Set, List, Tuple
from enum import Enum

class LabelType(Enum):
    CODE = "code"
    DATA = "data"
    ALIAS = "alias"
    UNKNOWN = "unknown"

class AssemblyLabelAnalyzer:
    def __init__(self, assembly_file: str, format_type: str = "auto"):
        self.assembly_file = assembly_file
        self.format_type = format_type
        self.lines = []
        self.labels: Dict[str, LabelType] = {}
        self.label_line_map: Dict[str, int] = {}
        self.label_analysis: Dict[str, Dict] = {}
        
        # 6502 instruction set
        self.instructions = {
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
            'brk', 'nop'
        }
        
        # Data directive patterns
        self.data_directives = {'.db', '.dw', '.byte', '.word', '.res', '.byt'}
        
        self._load_assembly()
        self._detect_format()
    
    def _load_assembly(self):
        """Load assembly file and split into lines"""
        try:
            with open(self.assembly_file, 'r', encoding='utf-8', errors='ignore') as f:
                self.lines = f.readlines()
            print(f"Loaded {len(self.lines)} lines from {self.assembly_file}")
        except FileNotFoundError:
            print(f"Error: Could not find file {self.assembly_file}")
            sys.exit(1)
    
    def _detect_format(self):
        """Auto-detect assembly format (CA65, original, etc.)"""
        if self.format_type != "auto":
            return
        
        ca65_indicators = 0
        original_indicators = 0
        
        for line in self.lines[:100]:  # Check first 100 lines
            line = line.strip().lower()
            
            # CA65 indicators
            if any(indicator in line for indicator in ['.segment', '.proc', '.endproc', '@', '::']):
                ca65_indicators += 1
            
            # Look for addressing mode prefixes
            if re.search(r'\b[az]:', line):
                ca65_indicators += 1
            
            # Original format indicators
            if line.startswith('*') or '$' in line:
                original_indicators += 1
        
        self.format_type = "ca65" if ca65_indicators > original_indicators else "original"
        print(f"Detected format: {self.format_type}")
    
    def analyze_labels(self):
        """Find and analyze all labels in the assembly code"""
        print("Analyzing labels...")
        
        # Find all labels
        self._find_all_labels()
        
        # Analyze each label's content
        for label_name, line_num in self.label_line_map.items():
            analysis = self._analyze_label_content(label_name, line_num)
            self.label_analysis[label_name] = analysis
            self.labels[label_name] = self._classify_label(label_name, analysis)
        
        print(f"Found {len(self.labels)} labels")
        self._print_classification_summary()
    
    def _find_all_labels(self):
        """Find all labels in the assembly code"""
        if self.format_type == "ca65":
            patterns = [
                re.compile(r'^([a-zA-Z_][a-zA-Z0-9_]*):'),  # standard labels
                re.compile(r'^(@[a-zA-Z_][a-zA-Z0-9_]*):'), # local labels
                re.compile(r'^(::?[a-zA-Z_][a-zA-Z0-9_]*):'), # global labels
            ]
        else:
            patterns = [
                re.compile(r'^([a-zA-Z_][a-zA-Z0-9_]*):'),  # standard labels
            ]
        
        for line_num, line in enumerate(self.lines):
            line_stripped = line.strip()
            
            for pattern in patterns:
                match = pattern.match(line_stripped)
                if match:
                    label_name = match.group(1)
                    # Clean up label name (remove @ and :: prefixes for analysis)
                    clean_name = label_name.lstrip('@:')
                    self.label_line_map[clean_name] = line_num
                    break
    
    def _analyze_label_content(self, label_name: str, start_line: int) -> Dict:
        """Analyze the content following a label"""
        analysis = {
            'instruction_count': 0,
            'data_directive_count': 0,
            'jump_target_count': 0,
            'first_instruction': None,
            'has_only_data': True,
            'has_only_instructions': True,
            'content_lines': 0,
            'sample_content': []
        }
        
        # Look at content after the label
        max_lines = min(20, len(self.lines) - start_line - 1)
        
        for i in range(1, max_lines + 1):
            line_num = start_line + i
            if line_num >= len(self.lines):
                break
            
            line = self.lines[line_num].strip()
            
            # Skip empty lines and comments
            if not line or line.startswith(';'):
                continue
            
            # Stop at next label
            if self._is_label_line(line):
                break
            
            analysis['content_lines'] += 1
            if len(analysis['sample_content']) < 5:
                analysis['sample_content'].append(line)
            
            # Check for instructions
            if self._contains_instruction(line):
                analysis['instruction_count'] += 1
                analysis['has_only_data'] = False
                if not analysis['first_instruction']:
                    analysis['first_instruction'] = line.split()[0].lower()
            
            # Check for data directives
            elif self._contains_data_directive(line):
                analysis['data_directive_count'] += 1
                analysis['has_only_instructions'] = False
            
            # Check for jump targets
            elif self._is_jump_target(line):
                analysis['jump_target_count'] += 1
                analysis['has_only_data'] = False
                analysis['has_only_instructions'] = False
            
            else:
                # Unknown content
                analysis['has_only_data'] = False
                analysis['has_only_instructions'] = False
        
        return analysis
    
    def _is_label_line(self, line: str) -> bool:
        """Check if line contains a label"""
        if self.format_type == "ca65":
            patterns = [
                r'^[a-zA-Z_][a-zA-Z0-9_]*:',
                r'^@[a-zA-Z_][a-zA-Z0-9_]*:',
                r'^::?[a-zA-Z_][a-zA-Z0-9_]*:',
            ]
        else:
            patterns = [r'^[a-zA-Z_][a-zA-Z0-9_]*:']
        
        for pattern in patterns:
            if re.match(pattern, line):
                return True
        return False
    
    def _contains_instruction(self, line: str) -> bool:
        """Check if line contains a 6502 instruction"""
        # Remove comments and split
        line_clean = line.split(';')[0].strip().lower()
        tokens = line_clean.split()
        
        if tokens and tokens[0] in self.instructions:
            return True
        return False
    
    def _contains_data_directive(self, line: str) -> bool:
        """Check if line contains data directives"""
        line_clean = line.split(';')[0].strip().lower()
        tokens = line_clean.split()
        
        if tokens and tokens[0] in self.data_directives:
            return True
        return False
    
    def _is_jump_target(self, line: str) -> bool:
        """Check if line is a simple jump to another label"""
        line_clean = line.split(';')[0].strip().lower()
        tokens = line_clean.split()
        
        if len(tokens) >= 2 and tokens[0] in ['jmp', 'jsr']:
            target = tokens[1]
            # Check if target looks like a label
            if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', target):
                return True
        return False
    
    def _classify_label(self, label_name: str, analysis: Dict) -> LabelType:
        """Classify a label based on its analysis"""
        # Strong data indicators
        if (analysis['data_directive_count'] > 0 and 
            analysis['instruction_count'] == 0 and
            analysis['has_only_data']):
            return LabelType.DATA
        
        # Strong alias indicators
        if (analysis['content_lines'] <= 2 and 
            analysis['jump_target_count'] > 0 and
            analysis['instruction_count'] == 0 and
            analysis['data_directive_count'] == 0):
            return LabelType.ALIAS
        
        # Code indicators
        if analysis['instruction_count'] > 0:
            return LabelType.CODE
        
        # Special patterns
        if analysis['first_instruction'] in ['jmp', 'jsr'] and analysis['content_lines'] == 1:
            return LabelType.ALIAS
        
        # Default to code for safety (prevents goto compilation errors)
        if analysis['content_lines'] == 0:
            return LabelType.CODE
        
        return LabelType.CODE
    
    def _print_classification_summary(self):
        """Print summary of label classification"""
        code_count = sum(1 for t in self.labels.values() if t == LabelType.CODE)
        data_count = sum(1 for t in self.labels.values() if t == LabelType.DATA)
        alias_count = sum(1 for t in self.labels.values() if t == LabelType.ALIAS)
        
        print(f"\nLabel Classification Summary:")
        print(f"  CODE labels: {code_count}")
        print(f"  DATA labels: {data_count}")
        print(f"  ALIAS labels: {alias_count}")
        print(f"  Total: {len(self.labels)}")
    
    def generate_config_files(self, output_dir: str):
        """Generate configuration files"""
        output_path = Path(output_dir)
        output_path.mkdir(exist_ok=True)
        
        print(f"\nGenerating configuration files in {output_dir}...")
        
        # Generate individual classification files
        self._generate_code_labels_config(output_path)
        self._generate_data_labels_config(output_path)
        self._generate_alias_labels_config(output_path)
        
        # Generate analysis report
        self._generate_analysis_report(output_path)
        
        # Generate usage guide
        self._generate_usage_guide(output_path)
        
        print("Configuration files generated successfully!")
    
    def _generate_code_labels_config(self, output_path: Path):
        """Generate code labels configuration file"""
        config_file = output_path / "code_labels.txt"
        
        code_labels = [name for name, ltype in self.labels.items() if ltype == LabelType.CODE]
        
        with open(config_file, 'w') as f:
            f.write("# Code Labels Configuration\n")
            f.write("# Labels that should be treated as CODE (for goto statements)\n")
            f.write("# One label per line, lines starting with # are comments\n")
            f.write("#\n")
            f.write(f"# Auto-detected {len(code_labels)} code labels:\n")
            f.write("#\n")
            
            for label in sorted(code_labels):
                analysis = self.label_analysis[label]
                f.write(f"{label}")
                if analysis['first_instruction']:
                    f.write(f"  # starts with: {analysis['first_instruction']}")
                f.write("\n")
        
        print(f"  Generated {config_file} with {len(code_labels)} labels")
    
    def _generate_data_labels_config(self, output_path: Path):
        """Generate data labels configuration file"""
        config_file = output_path / "data_labels.txt"
        
        data_labels = [name for name, ltype in self.labels.items() if ltype == LabelType.DATA]
        
        with open(config_file, 'w') as f:
            f.write("# Data Labels Configuration\n")
            f.write("# Labels that should be treated as DATA (generate data pointers)\n")
            f.write("# One label per line, lines starting with # are comments\n")
            f.write("#\n")
            f.write(f"# Auto-detected {len(data_labels)} data labels:\n")
            f.write("#\n")
            
            for label in sorted(data_labels):
                analysis = self.label_analysis[label]
                f.write(f"{label}")
                if analysis['data_directive_count'] > 0:
                    f.write(f"  # {analysis['data_directive_count']} data directives")
                f.write("\n")
        
        print(f"  Generated {config_file} with {len(data_labels)} labels")
    
    def _generate_alias_labels_config(self, output_path: Path):
        """Generate alias labels configuration file"""
        config_file = output_path / "alias_labels.txt"
        
        alias_labels = [name for name, ltype in self.labels.items() if ltype == LabelType.ALIAS]
        
        with open(config_file, 'w') as f:
            f.write("# Alias Labels Configuration\n")
            f.write("# Labels that are simple aliases to other labels\n")
            f.write("# One label per line, lines starting with # are comments\n")
            f.write("#\n")
            f.write(f"# Auto-detected {len(alias_labels)} alias labels:\n")
            f.write("#\n")
            
            for label in sorted(alias_labels):
                analysis = self.label_analysis[label]
                f.write(f"{label}")
                if analysis['sample_content']:
                    f.write(f"  # {analysis['sample_content'][0]}")
                f.write("\n")
        
        print(f"  Generated {config_file} with {len(alias_labels)} labels")
    
    def _generate_analysis_report(self, output_path: Path):
        """Generate detailed analysis report"""
        report_file = output_path / "label_analysis_report.txt"
        
        with open(report_file, 'w') as f:
            f.write("6502 Assembly Label Analysis Report\n")
            f.write("=" * 50 + "\n\n")
            
            f.write(f"Input file: {self.assembly_file}\n")
            f.write(f"Detected format: {self.format_type}\n")
            f.write(f"Total lines: {len(self.lines)}\n")
            f.write(f"Total labels: {len(self.labels)}\n\n")
            
            # Summary by type
            for label_type in LabelType:
                labels_of_type = [name for name, ltype in self.labels.items() if ltype == label_type]
                f.write(f"{label_type.name} LABELS ({len(labels_of_type)}):\n")
                f.write("-" * 30 + "\n")
                
                for label in sorted(labels_of_type):
                    analysis = self.label_analysis[label]
                    f.write(f"\n{label}:\n")
                    f.write(f"  Instructions: {analysis['instruction_count']}\n")
                    f.write(f"  Data directives: {analysis['data_directive_count']}\n")
                    f.write(f"  Content lines: {analysis['content_lines']}\n")
                    
                    if analysis['sample_content']:
                        f.write(f"  Sample content:\n")
                        for line in analysis['sample_content'][:3]:
                            f.write(f"    {line}\n")
                
                f.write("\n")
        
        print(f"  Generated {report_file}")
    
    def _generate_usage_guide(self, output_path: Path):
        """Generate usage guide"""
        guide_file = output_path / "USAGE_GUIDE.txt"
        
        with open(guide_file, 'w') as f:
            f.write("6502 Assembly Label Analyzer - Usage Guide\n")
            f.write("=" * 50 + "\n\n")
            
            f.write("GENERATED FILES:\n")
            f.write("  code_labels.txt  - Labels for goto statements\n")
            f.write("  data_labels.txt  - Labels for data pointers\n")
            f.write("  alias_labels.txt - Simple label aliases\n")
            f.write("  label_analysis_report.txt - Detailed analysis\n\n")
            
            f.write("HOW TO USE:\n")
            f.write("1. Review the generated files\n")
            f.write("2. Edit files to correct any misclassifications\n")
            f.write("3. Add/remove labels as needed\n")
            f.write("4. Use these files with your 6502 translator\n\n")
            
            f.write("EDITING TIPS:\n")
            f.write("- Add # at start of line to comment out a label\n")
            f.write("- Move labels between files to change classification\n")
            f.write("- CODE labels are used for goto statements\n")
            f.write("- DATA labels generate data pointers\n")
            f.write("- ALIAS labels are simple redirects\n\n")
            
            f.write("COMMON ISSUES:\n")
            f.write("- If you get 'undefined label' errors, move the label to code_labels.txt\n")
            f.write("- If data isn't accessible, move the label to data_labels.txt\n")
            f.write("- Check the analysis report for detailed label information\n")
        
        print(f"  Generated {guide_file}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python label_analyzer.py <assembly_file> [output_directory] [format]")
        print("")
        print("Arguments:")
        print("  assembly_file     - Path to the 6502 assembly file")
        print("  output_directory  - Directory for config files (default: label_config)")
        print("  format           - Assembly format: auto, ca65, original (default: auto)")
        print("")
        print("Examples:")
        print("  python label_analyzer.py game.asm")
        print("  python label_analyzer.py game.asm my_config")
        print("  python label_analyzer.py game.asm config ca65")
        sys.exit(1)
    
    assembly_file = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else "label_config"
    format_type = sys.argv[3] if len(sys.argv) > 3 else "auto"
    
    if not os.path.exists(assembly_file):
        print(f"Error: Assembly file '{assembly_file}' not found")
        sys.exit(1)
    
    try:
        # Create analyzer
        analyzer = AssemblyLabelAnalyzer(assembly_file, format_type)
        
        # Analyze labels
        analyzer.analyze_labels()
        
        # Generate config files
        analyzer.generate_config_files(output_dir)
        
        print(f"\nDone! Check the '{output_dir}' directory for configuration files.")
        print("Review and edit the files as needed, then use them with your 6502 translator.")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
