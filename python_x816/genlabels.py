#!/usr/bin/env python3
"""
6502 Assembly Label Analyzer - Enhanced Version
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
            'sample_content': [],
            'consecutive_data_lines': 0,
            'max_consecutive_data': 0,
            'data_to_instruction_ratio': 0
        }
        
        # Look at content after the label - increase range for better analysis
        max_lines = min(50, len(self.lines) - start_line - 1)
        consecutive_data = 0
        
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
            if len(analysis['sample_content']) < 10:  # Keep more samples
                analysis['sample_content'].append(line)
            
            # Check for instructions
            if self._contains_instruction(line):
                analysis['instruction_count'] += 1
                analysis['has_only_data'] = False
                consecutive_data = 0  # Reset consecutive data counter
                if not analysis['first_instruction']:
                    analysis['first_instruction'] = line.split()[0].lower()
            
            # Check for data directives
            elif self._contains_data_directive(line):
                analysis['data_directive_count'] += 1
                analysis['has_only_instructions'] = False
                consecutive_data += 1
                analysis['max_consecutive_data'] = max(analysis['max_consecutive_data'], consecutive_data)
            
            # Check for jump targets
            elif self._is_jump_target(line):
                analysis['jump_target_count'] += 1
                analysis['has_only_data'] = False
                analysis['has_only_instructions'] = False
                consecutive_data = 0
            
            else:
                # Unknown content - might be comments, labels, etc.
                analysis['has_only_data'] = False
                analysis['has_only_instructions'] = False
                consecutive_data = 0
        
        # Calculate data to instruction ratio
        if analysis['instruction_count'] > 0:
            analysis['data_to_instruction_ratio'] = analysis['data_directive_count'] / analysis['instruction_count']
        elif analysis['data_directive_count'] > 0:
            analysis['data_to_instruction_ratio'] = float('inf')  # Only data, no instructions
        
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
        """Classify a label based on its actual content analysis"""
        
        # Pure data: Only data directives, no instructions
        if (analysis['data_directive_count'] > 0 and 
            analysis['instruction_count'] == 0 and
            analysis['has_only_data']):
            return LabelType.DATA
        
        # Predominantly data: Multiple data directives with minimal or no instructions
        if (analysis['data_directive_count'] >= 3 and 
            analysis['instruction_count'] <= 1):
            return LabelType.DATA
        
        # Data-heavy content: More data than instructions
        if (analysis['data_directive_count'] > 0 and 
            analysis['data_directive_count'] > analysis['instruction_count'] and
            analysis['content_lines'] >= 2):
            return LabelType.DATA
        
        # Simple alias: Very short content that just jumps to another label
        if (analysis['content_lines'] <= 2 and 
            analysis['jump_target_count'] > 0 and
            analysis['instruction_count'] <= 1 and
            analysis['data_directive_count'] == 0):
            return LabelType.ALIAS
        
        # Single instruction alias
        if (analysis['content_lines'] == 1 and 
            analysis['first_instruction'] in ['jmp', 'jsr']):
            return LabelType.ALIAS
        
        # Code: Contains instructions
        if analysis['instruction_count'] > 0:
            return LabelType.CODE
        
        # ENHANCED EMPTY LABEL HANDLING
        if analysis['content_lines'] == 0:
            # For empty labels, use contextual analysis
            data_probability = self._analyze_empty_label_context(label_name)
            
            if data_probability >= 0.7:  # High confidence it's data
                return LabelType.DATA
            elif data_probability <= 0.3:  # High confidence it's code
                return LabelType.CODE
            else:
                # Medium confidence - use safe default but flag for review
                return LabelType.CODE
        
        # If we have content but no clear classification, check the actual content
        if analysis['sample_content']:
            for line in analysis['sample_content']:
                line_lower = line.lower().strip()
                
                # Check for data-like content patterns
                if any(directive in line_lower for directive in ['.db', '.dw', '.byte', '.word']):
                    return LabelType.DATA
                
                # Check for immediate alias patterns  
                if line_lower.startswith('jmp ') or line_lower.startswith('jsr '):
                    # If this is the only/main content, it's likely an alias
                    if analysis['content_lines'] <= 2:
                        return LabelType.ALIAS
                    else:
                        return LabelType.CODE
                
                # Any other instruction indicates code
                if any(instr in line_lower.split() for instr in self.instructions):
                    return LabelType.CODE
        
        # Default to CODE for safety (prevents compilation errors)
        return LabelType.CODE
    
    def _analyze_empty_label_context(self, label_name: str) -> float:
        """
        Analyze context around empty labels to predict if they're data or code.
        Returns probability (0.0-1.0) that label is DATA.
        """
        data_score = 0.0
        total_indicators = 0
        
        # Find the label's line number
        label_line = self.label_line_map.get(label_name, -1)
        if label_line == -1:
            return 0.5  # Unknown, neutral score
        
        # PATTERN 1: Check surrounding labels for data patterns
        nearby_data_labels = 0
        nearby_code_labels = 0
        
        # Look at labels within ±10 lines
        for other_label, other_line in self.label_line_map.items():
            if other_label == label_name:
                continue
            
            line_distance = abs(other_line - label_line)
            if line_distance <= 10:
                other_analysis = self.label_analysis.get(other_label, {})
                if other_analysis.get('data_directive_count', 0) > 0:
                    nearby_data_labels += 1
                elif other_analysis.get('instruction_count', 0) > 0:
                    nearby_code_labels += 1
        
        if nearby_data_labels + nearby_code_labels > 0:
            total_indicators += 1
            data_score += nearby_data_labels / (nearby_data_labels + nearby_code_labels)
        
        # PATTERN 2: Common data label naming patterns
        name_lower = label_name.lower()
        
        # Strong data indicators
        strong_data_patterns = [
            'data', 'table', 'tbl', 'offset', 'addr', 'palette', 'color',
            'hdr', 'header', 'music', 'sound', 'sfx', 'mus', 'graphics', 'gfx',
            'tiles', 'mtiles', 'text', 'message', 'msg', 'speed', 'timer',
            'freq', 'envelope', 'env', 'pos', 'adder', 'lookup'
        ]
        
        strong_data_score = sum(1 for pattern in strong_data_patterns if pattern in name_lower)
        if strong_data_score > 0:
            total_indicators += 1
            data_score += min(1.0, strong_data_score * 0.3)  # Cap contribution
        
        # PATTERN 3: Array/collection patterns
        array_patterns = [
            ('world', 'areas'), ('e_', 'area'), ('l_', 'area'),
            ('area', 'data'), ('enemy', 'data'), ('player', 'data')
        ]
        
        for prefix, suffix in array_patterns:
            if prefix in name_lower and suffix in name_lower:
                total_indicators += 1
                data_score += 0.8
                break
        
        # PATTERN 4: Suffix patterns for data
        data_suffixes = ['data', 'hdr', 'offsets', 'table', 'tbl', 'palette', 'colors']
        if any(name_lower.endswith(suffix) for suffix in data_suffixes):
            total_indicators += 1
            data_score += 0.7
        
        # PATTERN 5: Prefix patterns for area/enemy data
        data_prefixes = ['e_', 'l_', 'world', 'area', 'enemy', 'player']
        if any(name_lower.startswith(prefix) for prefix in data_prefixes):
            total_indicators += 1
            data_score += 0.6
        
        # PATTERN 6: Check lines before label for context clues
        context_lines = self._get_lines_before_label(label_line, 5)
        data_context_clues = 0
        code_context_clues = 0
        
        for line in context_lines:
            line_lower = line.lower()
            if any(directive in line_lower for directive in ['.db', '.dw', '.byte', '.word']):
                data_context_clues += 1
            elif any(instr in line_lower.split() for instr in self.instructions):
                code_context_clues += 1
        
        if data_context_clues + code_context_clues > 0:
            total_indicators += 1
            data_score += data_context_clues / (data_context_clues + code_context_clues)
        
        # PATTERN 7: Check lines after label (further ahead) for data blocks
        future_lines = self._get_lines_after_label(label_line, 20, 50)
        future_data_count = 0
        future_code_count = 0
        
        for line in future_lines:
            line_lower = line.lower()
            if any(directive in line_lower for directive in ['.db', '.dw', '.byte', '.word']):
                future_data_count += 1
            elif any(instr in line_lower.split() for instr in self.instructions):
                future_code_count += 1
        
        if future_data_count + future_code_count > 0:
            total_indicators += 1
            # Weight this less since it's further away
            data_score += 0.3 * (future_data_count / (future_data_count + future_code_count))
        
        # Calculate final probability
        if total_indicators == 0:
            return 0.5  # No indicators, neutral
        
        probability = data_score / total_indicators
        
        # Apply some bounds and adjustments
        probability = max(0.0, min(1.0, probability))
        
        # Add debug info for empty labels with high confidence
        if probability >= 0.7 or probability <= 0.3:
            self.label_analysis[label_name]['empty_label_analysis'] = {
                'probability': probability,
                'indicators': total_indicators,
                'raw_score': data_score,
                'classification': 'DATA' if probability >= 0.7 else 'CODE'
            }
        
        return probability
    
    def _get_lines_before_label(self, label_line: int, count: int) -> List[str]:
        """Get lines before a label for context analysis"""
        lines = []
        start = max(0, label_line - count)
        for i in range(start, label_line):
            if i < len(self.lines):
                line = self.lines[i].strip()
                if line and not line.startswith(';'):  # Skip empty lines and comments
                    lines.append(line)
        return lines
    
    def _get_lines_after_label(self, label_line: int, skip: int, count: int) -> List[str]:
        """Get lines after a label, skipping some lines first"""
        lines = []
        start = label_line + 1 + skip
        end = min(len(self.lines), start + count)
        
        for i in range(start, end):
            line = self.lines[i].strip()
            if line and not line.startswith(';'):  # Skip empty lines and comments
                # Stop if we hit another label
                if self._is_label_line(line):
                    break
                lines.append(line)
        return lines
    
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
                elif analysis['content_lines'] == 0:
                    f.write(f"  # empty label")
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
            f.write("# Examples of typical data labels:\n")
            f.write("# GameText\n")
            f.write("# AreaAddrOffsets\n")
            f.write("# MusicData\n")
            f.write("# PaletteData\n")
            f.write("#\n")
            f.write("# Add labels here that contain lookup tables, graphics data, etc.\n")
            f.write(f"# Auto-detected {len(data_labels)} data labels based on content analysis:\n")
            f.write("#\n")
            
            # Separate empty labels from content-based labels
            empty_data_labels = []
            content_data_labels = []
            
            for label in sorted(data_labels):
                analysis = self.label_analysis[label]
                if analysis['content_lines'] == 0:
                    empty_data_labels.append(label)
                else:
                    content_data_labels.append(label)
            
            # Write content-based data labels first
            if content_data_labels:
                f.write("# Labels with actual data content:\n")
                for label in content_data_labels:
                    analysis = self.label_analysis[label]
                    f.write(f"{label}")
                    
                    # Add analysis info as comment
                    if analysis['data_directive_count'] > 0:
                        f.write(f"  # {analysis['data_directive_count']} data directives")
                        if analysis['max_consecutive_data'] >= 3:
                            f.write(f", {analysis['max_consecutive_data']} consecutive")
                        if analysis['instruction_count'] > 0:
                            f.write(f", {analysis['instruction_count']} instructions")
                    else:
                        f.write(f"  # content analysis classified as data")
                    
                    f.write("\n")
            
            # Write empty labels that were auto-classified as data
            if empty_data_labels:
                f.write(f"\n# Empty labels auto-classified as DATA (based on context analysis):\n")
                f.write("# These labels have no content but patterns suggest they are data pointers\n")
                for label in empty_data_labels:
                    analysis = self.label_analysis[label]
                    f.write(f"{label}")
                    
                    if 'empty_label_analysis' in analysis:
                        empty_analysis = analysis['empty_label_analysis']
                        f.write(f"  # auto-classified: {empty_analysis['probability']:.2f} confidence")
                    else:
                        f.write(f"  # empty label - review classification")
                    
                    f.write("\n")
        
        print(f"  Generated {config_file} with {len(data_labels)} labels")
        
        if empty_data_labels:
            print(f"    - {len(content_data_labels)} labels with actual data content")
            print(f"    - {len(empty_data_labels)} empty labels auto-classified as DATA")
            print(f"    Check the analysis report for empty label classification details")
    
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
                    
                    # Add empty label analysis if available
                    if 'empty_label_analysis' in analysis:
                        empty_analysis = analysis['empty_label_analysis']
                        f.write(f"  Empty label analysis:\n")
                        f.write(f"    Probability (DATA): {empty_analysis['probability']:.2f}\n")
                        f.write(f"    Indicators found: {empty_analysis['indicators']}\n")
                        f.write(f"    Auto-classification: {empty_analysis['classification']}\n")
                    
                    if analysis['sample_content']:
                        f.write(f"  Sample content:\n")
                        for line in analysis['sample_content'][:3]:
                            f.write(f"    {line}\n")
                
                f.write("\n")
            
            # Special section for empty labels that were auto-classified as DATA
            empty_data_labels = []
            for label, ltype in self.labels.items():
                if (ltype == LabelType.DATA and 
                    self.label_analysis[label]['content_lines'] == 0 and
                    'empty_label_analysis' in self.label_analysis[label]):
                    empty_data_labels.append(label)
            
            if empty_data_labels:
                f.write("\nEMPTY LABELS AUTO-CLASSIFIED AS DATA:\n")
                f.write("-" * 40 + "\n")
                f.write("These labels had no content but were classified as DATA\n")
                f.write("based on contextual analysis (naming patterns, nearby labels, etc.)\n\n")
                
                for label in sorted(empty_data_labels):
                    analysis = self.label_analysis[label]['empty_label_analysis']
                    f.write(f"{label}: {analysis['probability']:.2f} confidence\n")
        
        print(f"  Generated {report_file}")
    
    def _generate_usage_guide(self, output_path: Path):
        """Generate usage guide"""
        guide_file = output_path / "USAGE_GUIDE.txt"
        
        with open(guide_file, 'w') as f:
            f.write("6502 Assembly Label Analyzer - Enhanced Usage Guide\n")
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
            
            f.write("CONTENT-BASED CLASSIFICATION:\n")
            f.write("This analyzer classifies labels based on what actually follows them:\n")
            f.write("- DATA: Labels followed primarily by .db/.dw/.byte/.word directives\n")
            f.write("- CODE: Labels followed by 6502 instructions (lda, sta, jmp, etc.)\n")
            f.write("- ALIAS: Labels with single jmp/jsr to another label\n\n")
            
            f.write("ENHANCED EMPTY LABEL ANALYSIS:\n")
            f.write("For empty labels (no content), the analyzer uses contextual clues:\n")
            f.write("- Naming patterns (Data, Hdr, Table, Offset, Music, etc.)\n")
            f.write("- Array patterns (World*Areas, E_*Area*, L_*Area*)\n")
            f.write("- Surrounding label types\n")
            f.write("- Context before/after the label\n")
            f.write("- High confidence (>=70%) auto-classifies as DATA\n")
            f.write("- Low confidence (<=30%) auto-classifies as CODE\n")
            f.write("- Medium confidence defaults to CODE (safer)\n\n")
            
            f.write("CLASSIFICATION CRITERIA:\n")
            f.write("- Pure DATA: Only data directives, no instructions\n")
            f.write("- Predominantly DATA: 3+ data directives, ≤1 instruction\n")
            f.write("- Data-heavy: More data directives than instructions\n")
            f.write("- Simple ALIAS: ≤2 lines with jump to another label\n")
            f.write("- CODE: Contains any 6502 instructions\n")
            f.write("- Empty labels: Use contextual analysis with confidence scoring\n\n")
            
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
            f.write("- Empty labels with low confidence may need manual review\n")
            f.write("- Mixed content (data + instructions) defaults to CODE\n\n")
            
            f.write("CONFIDENCE INDICATORS FOR EMPTY LABELS:\n")
            f.write("- High confidence DATA: Contains 'Hdr', 'Data', 'Table', 'Areas'\n")
            f.write("- Medium confidence DATA: Starts with 'E_', 'L_', 'World'\n")
            f.write("- Review labels with medium confidence (30-70%) manually\n")
        
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
        print("The analyzer now includes enhanced empty label detection!")
        print("Review and edit the files as needed, then use them with your 6502 translator.")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
