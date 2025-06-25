#!/usr/bin/env python3
"""
CA65 Listing File Analyzer
Analyzes ca65 listing files to automatically generate label configuration files
Much more accurate than parsing raw assembly since ca65 has already done the hard work!
"""

import sys
import os
from pathlib import Path
from typing import Dict, Set, List, Tuple, Optional
from enum import Enum

class LabelType(Enum):
    CODE = "code"
    DATA = "data"
    ALIAS = "alias"
    UNKNOWN = "unknown"

class ListingLineType(Enum):
    LABEL = "label"
    INSTRUCTION = "instruction" 
    DATA = "data"
    EMPTY = "empty"
    COMMENT = "comment"

class CA65ListingAnalyzer:
    def __init__(self, listing_file: str):
        self.listing_file = listing_file
        self.lines = []
        self.labels: Dict[str, LabelType] = {}
        self.label_analysis: Dict[str, Dict] = {}
        self.parsed_lines: List[Dict] = []
        
        # 6502/65816 instruction patterns
        self.instructions = {
            'lda', 'ldx', 'ldy', 'sta', 'stx', 'sty',
            'tax', 'tay', 'txa', 'tya', 'tsx', 'txs',
            'pha', 'php', 'pla', 'plp', 'phx', 'phy', 'plx', 'ply',  # 65816 additions
            'and', 'eor', 'ora', 'bit',
            'adc', 'sbc', 'cmp', 'cpx', 'cpy',
            'inc', 'inx', 'iny', 'dec', 'dex', 'dey',
            'asl', 'lsr', 'rol', 'ror',
            'jmp', 'jsr', 'rts', 'rti', 'rtl',  # rtl for 65816
            'bcc', 'bcs', 'beq', 'bmi', 'bne', 'bpl', 'bvc', 'bvs',
            'clc', 'cld', 'cli', 'clv', 'sec', 'sed', 'sei',
            'brk', 'nop', 'wdm', 'cop',  # 65816 additions
            # 65816 specific instructions
            'brl', 'jml', 'jsl', 'mvn', 'mvp', 'pea', 'pei', 'per',
            'phb', 'phd', 'phk', 'plb', 'pld', 'rep', 'sep', 'tcd',
            'tcs', 'tdc', 'tsc', 'txy', 'tyx', 'xba', 'xce'
        }
        
        # Data directive patterns (ca65 format)
        self.data_directives = {'.byte', '.word', '.dword', '.addr', '.faraddr', '.res', '.org'}
        
        self._load_listing()
        self._parse_listing()
    
    def _load_listing(self):
        """Load ca65 listing file"""
        try:
            with open(self.listing_file, 'r', encoding='utf-8', errors='ignore') as f:
                self.lines = f.readlines()
            print(f"Loaded {len(self.lines)} lines from {self.listing_file}")
        except FileNotFoundError:
            print(f"Error: Could not find listing file {self.listing_file}")
            print("Generate it with: ca65 -l output.lst input.asm")
            sys.exit(1)
    
    def _parse_listing(self):
        """Parse ca65 listing file format"""
        print("Parsing ca65 listing file...")
        
        for line_num, line in enumerate(self.lines):
            parsed = self._parse_listing_line(line, line_num)
            if parsed:
                self.parsed_lines.append(parsed)
        
        print(f"Parsed {len(self.parsed_lines)} meaningful lines")
    
    def _is_hex_char(self, c: str) -> bool:
        """Check if character is a hex digit"""
        return c in '0123456789ABCDEFabcdef'
    
    def _is_hex_string(self, s: str) -> bool:
        """Check if string contains only hex characters and spaces"""
        for c in s:
            if not (self._is_hex_char(c) or c.isspace()):
                return False
        return True
    
    def _is_valid_address(self, s: str) -> bool:
        """Check if string looks like a valid address (hex chars + optional 'r')"""
        if not s:
            return False
        if s.endswith('r'):
            s = s[:-1]
        return len(s) > 0 and all(self._is_hex_char(c) for c in s)
    
    def _is_valid_label_name(self, s: str) -> bool:
        """Check if string looks like a valid label name"""
        if not s:
            return False
        # Must start with letter or underscore
        if not (s[0].isalpha() or s[0] == '_'):
            return False
        # Rest must be alphanumeric or underscore
        for c in s[1:]:
            if not (c.isalnum() or c == '_'):
                return False
        return True
    
    def _extract_hex_bytes(self, s: str) -> Tuple[str, str]:
        """Extract hex bytes from start of string, return (hex_part, rest)"""
        hex_part = ""
        i = 0
        
        while i < len(s):
            # Skip whitespace
            while i < len(s) and s[i].isspace():
                hex_part += s[i]
                i += 1
            
            # Check for 2-character hex sequence
            if i + 1 < len(s) and self._is_hex_char(s[i]) and self._is_hex_char(s[i + 1]):
                hex_part += s[i:i + 2]
                i += 2
            else:
                break
        
        # Must have significant whitespace after hex bytes for source code
        rest = s[i:]
        if rest.startswith('  ') or rest.startswith('\t'):
            return hex_part.strip(), rest.lstrip()
        else:
            # No clear separation, treat everything as source
            return "", s
    
    def _parse_listing_line(self, line: str, line_num: int) -> Optional[Dict]:
        """
        Parse a single line from ca65 listing file
        
        CA65 listing format examples:
        000000r 1               ; Comment
        000000r 1  A9 01        lda #$01
        000002r 1  8D 00 20     sta $2000
        000005r 1               Label:
        000005r 1  60           rts
                2               .include "header.inc"
        """
        
        # Skip completely empty lines
        if not line.strip():
            return None
        
        # Remove trailing newline
        line = line.rstrip('\n\r')
        
        # Skip header lines and non-code lines
        if line.startswith('ca65') or line.startswith('------') or not line.strip():
            return None
        
        result = {
            'line_num': line_num,
            'address': None,
            'source_line': None,
            'bytes': None,
            'source_code': '',
            'type': ListingLineType.EMPTY,
            'label': None,
            'instruction': None
        }
        
        # CA65 listing format is positional:
        # Columns 0-6: Address (like "000000r" or spaces)
        # Column 8+: Line number 
        # Column 12+: Hex bytes (if any)
        # Column 24+: Source code
        
        # Extract address if present (first 7 characters)
        addr_part = line[:7].strip()
        if addr_part and self._is_valid_address(addr_part):
            result['address'] = addr_part.rstrip('r')
        
        # Extract line number (look for digits after address)
        line_rest = line[8:].lstrip()
        if line_rest:
            # Look for line number at start
            line_num_str = ""
            i = 0
            while i < len(line_rest) and line_rest[i].isdigit():
                line_num_str += line_rest[i]
                i += 1
            
            if line_num_str:
                result['source_line'] = int(line_num_str)
                line_rest = line_rest[len(line_num_str):].lstrip()
        
        # The rest should be hex bytes (if any) followed by source code
        if line_rest:
            hex_bytes, source_code = self._extract_hex_bytes(line_rest)
            if hex_bytes:
                result['bytes'] = hex_bytes
            result['source_code'] = source_code
        
        # If we still don't have source code, try the original line
        if not result['source_code']:
            # For lines without proper CA65 format, just take everything after reasonable position
            if len(line) > 24:
                result['source_code'] = line[24:].strip()
            else:
                result['source_code'] = line.strip()
        
        # Only process lines that have actual source code or are structured
        if not result['source_code'] and not result['address']:
            return None
        
        # Analyze the source code
        self._analyze_source_line(result)
        
        return result
    
    def _analyze_source_line(self, parsed_line: Dict):
        """Analyze the source code portion of a listing line"""
        source = parsed_line['source_code'].strip()
        
        if not source or source.startswith(';'):
            parsed_line['type'] = ListingLineType.COMMENT
            return
        
        # Check for labels (end with :)
        if source.endswith(':'):
            parsed_line['type'] = ListingLineType.LABEL
            parsed_line['label'] = source[:-1].strip()
            return
        
        # Check for labels with code on same line
        if ':' in source and not source.startswith(';'):
            colon_pos = source.find(':')
            label_part = source[:colon_pos].strip()
            # Make sure this looks like a real label
            if self._is_valid_label_name(label_part):
                parsed_line['label'] = label_part
                rest = source[colon_pos + 1:].strip()
                if rest:
                    # Create a proper temporary parsed dict with all required keys
                    temp_parsed = {
                        'source_code': rest,
                        'address': parsed_line.get('address'),
                        'bytes': parsed_line.get('bytes'),
                        'type': ListingLineType.EMPTY,
                        'label': None,
                        'instruction': None
                    }
                    # Recurse to analyze the rest
                    self._analyze_source_line(temp_parsed)
                    parsed_line['type'] = temp_parsed.get('type', ListingLineType.INSTRUCTION)
                    parsed_line['instruction'] = temp_parsed.get('instruction')
                else:
                    parsed_line['type'] = ListingLineType.LABEL
                return
        
        # Check for data directives
        source_lower = source.lower()
        tokens = source_lower.split()
        
        if tokens and any(directive in tokens[0] for directive in self.data_directives):
            parsed_line['type'] = ListingLineType.DATA
            return
        
        # Check for instructions
        if tokens and tokens[0] in self.instructions:
            parsed_line['type'] = ListingLineType.INSTRUCTION
            parsed_line['instruction'] = tokens[0]
            return
        
        # Filter out lines that are clearly not labels or code
        # Skip lines that are just hex values or short patterns
        if len(source.strip()) <= 20 and self._is_hex_string(source.replace(' ', '')):
            return
        
        # Skip disassembly-like patterns (hex bytes followed by 3-letter instruction and addressing mode)
        tokens = source.split()
        if (len(tokens) >= 3 and 
            len(tokens[0]) == 2 and self._is_hex_string(tokens[0]) and
            len(tokens[-2]) == 3 and tokens[-2].lower() in self.instructions and
            len(tokens[-1]) == 1):
            return
        
        # Default to instruction if it has an address (assembled code)
        if parsed_line.get('address') and parsed_line.get('bytes'):
            parsed_line['type'] = ListingLineType.INSTRUCTION
        else:
            parsed_line['type'] = ListingLineType.EMPTY
    
    def analyze_labels(self):
        """Analyze labels found in the listing"""
        print("Analyzing labels from listing...")
        
        # First pass: collect all labels
        label_positions = {}
        for i, parsed in enumerate(self.parsed_lines):
            if parsed['label']:
                label_positions[parsed['label']] = i
        
        print(f"Found {len(label_positions)} labels")
        
        # Second pass: analyze what follows each label
        for label_name, pos in label_positions.items():
            analysis = self._analyze_label_context(label_name, pos)
            self.label_analysis[label_name] = analysis
            self.labels[label_name] = self._classify_label(label_name, analysis)
        
        self._print_classification_summary()
    
    def _analyze_label_context(self, label_name: str, start_pos: int) -> Dict:
        """Analyze what follows a label in the listing"""
        analysis = {
            'instruction_count': 0,
            'data_directive_count': 0,
            'alias_target': None,
            'first_instruction': None,
            'content_lines': 0,
            'sample_content': [],
            'max_consecutive_data': 0,
            'is_empty_label': True
        }
        
        consecutive_data = 0
        
        # Look at the next 20 lines after the label
        for i in range(start_pos + 1, min(len(self.parsed_lines), start_pos + 21)):
            parsed = self.parsed_lines[i]
            
            # Stop at next label
            if parsed['label'] and parsed['label'] != label_name:
                break
            
            if parsed['type'] == ListingLineType.INSTRUCTION:
                analysis['instruction_count'] += 1
                analysis['is_empty_label'] = False
                consecutive_data = 0
                
                if not analysis['first_instruction']:
                    analysis['first_instruction'] = parsed['instruction']
                
                # Check for simple aliases (single jmp/jsr)
                if (analysis['instruction_count'] == 1 and 
                    parsed['instruction'] in ['jmp', 'jsr'] and
                    analysis['data_directive_count'] == 0):
                    # Try to extract target
                    source = parsed['source_code']
                    # Look for jmp/jsr followed by a label name
                    tokens = source.split()
                    if len(tokens) >= 2:
                        target = tokens[1]
                        # Remove addressing mode characters
                        target = target.replace('#', '').replace('$', '').replace(',x', '').replace(',y', '')
                        if self._is_valid_label_name(target):
                            analysis['alias_target'] = target
            
            elif parsed['type'] == ListingLineType.DATA:
                analysis['data_directive_count'] += 1
                analysis['is_empty_label'] = False
                consecutive_data += 1
                analysis['max_consecutive_data'] = max(analysis['max_consecutive_data'], consecutive_data)
            
            if parsed['type'] in [ListingLineType.INSTRUCTION, ListingLineType.DATA]:
                analysis['content_lines'] += 1
                if len(analysis['sample_content']) < 5:
                    analysis['sample_content'].append(parsed['source_code'])
        
        return analysis
    
    def _classify_label(self, label_name: str, analysis: Dict) -> LabelType:
        """Classify a label based on listing analysis"""
        
        # Empty labels - use naming pattern analysis
        if analysis['is_empty_label']:
            data_probability = self._analyze_empty_label_patterns(label_name)
            if data_probability >= 0.7:
                return LabelType.DATA
            elif data_probability <= 0.3:
                return LabelType.CODE
            else:
                return LabelType.CODE  # Safe default
        
        # Simple alias detection
        if (analysis['alias_target'] and 
            analysis['instruction_count'] == 1 and 
            analysis['data_directive_count'] == 0):
            return LabelType.ALIAS
        
        # Pure data
        if (analysis['data_directive_count'] > 0 and 
            analysis['instruction_count'] == 0):
            return LabelType.DATA
        
        # Predominantly data
        if (analysis['data_directive_count'] >= 3 and 
            analysis['instruction_count'] <= 1):
            return LabelType.DATA
        
        # Data-heavy
        if (analysis['data_directive_count'] > 0 and 
            analysis['data_directive_count'] > analysis['instruction_count']):
            return LabelType.DATA
        
        # Everything else is code
        return LabelType.CODE
    
    def _analyze_empty_label_patterns(self, label_name: str) -> float:
        """Analyze empty label naming patterns to predict type"""
        name_lower = label_name.lower()
        data_score = 0.0
        total_patterns = 0
        
        # Strong data patterns
        data_patterns = [
            'data', 'table', 'tbl', 'offset', 'addr', 'palette', 'color',
            'hdr', 'header', 'music', 'sound', 'sfx', 'mus', 'graphics', 'gfx',
            'areas', 'text', 'message'
        ]
        
        for pattern in data_patterns:
            if pattern in name_lower:
                data_score += 0.3
                total_patterns += 1
        
        # Specific patterns
        if name_lower.startswith('world') and name_lower.endswith('areas'):
            data_score += 0.5
            total_patterns += 1
        
        if name_lower.endswith('hdr'):
            data_score += 0.4
            total_patterns += 1
        
        if name_lower.startswith(('e_', 'l_')) and 'area' in name_lower:
            data_score += 0.4
            total_patterns += 1
        
        # Anti-patterns (things that look like data but aren't)
        anti_patterns = ['move', 'sub', 'routine', 'handler', 'check', 'init']
        for pattern in anti_patterns:
            if pattern in name_lower:
                data_score -= 0.3
                total_patterns += 1
        
        if total_patterns == 0:
            return 0.5  # No patterns, neutral
        
        probability = data_score / total_patterns
        return max(0.0, min(1.0, probability + 0.5))  # Bias toward neutral
    
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
        
        self._generate_code_labels_config(output_path)
        self._generate_data_labels_config(output_path)
        self._generate_alias_labels_config(output_path)
        self._generate_analysis_report(output_path)
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
            f.write(f"# Auto-detected {len(code_labels)} code labels from ca65 listing:\n")
            f.write("#\n")
            
            for label in sorted(code_labels):
                analysis = self.label_analysis[label]
                f.write(f"{label}")
                if analysis['first_instruction']:
                    f.write(f"  # starts with: {analysis['first_instruction']}")
                elif analysis['is_empty_label']:
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
            f.write(f"# Auto-detected {len(data_labels)} data labels from ca65 listing:\n")
            f.write("#\n")
            
            content_labels = []
            empty_labels = []
            
            for label in sorted(data_labels):
                analysis = self.label_analysis[label]
                if analysis['is_empty_label']:
                    empty_labels.append(label)
                else:
                    content_labels.append(label)
            
            if content_labels:
                f.write("# Labels with actual data content:\n")
                for label in content_labels:
                    analysis = self.label_analysis[label]
                    f.write(f"{label}")
                    if analysis['data_directive_count'] > 0:
                        f.write(f"  # {analysis['data_directive_count']} data directives")
                        if analysis['max_consecutive_data'] >= 3:
                            f.write(f", {analysis['max_consecutive_data']} consecutive")
                    f.write("\n")
            
            if empty_labels:
                f.write(f"\n# Empty labels classified as DATA based on naming patterns:\n")
                for label in empty_labels:
                    f.write(f"{label}  # pattern-based classification\n")
        
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
            f.write(f"# Auto-detected {len(alias_labels)} alias labels from ca65 listing:\n")
            f.write("#\n")
            
            for label in sorted(alias_labels):
                analysis = self.label_analysis[label]
                f.write(f"{label}")
                if analysis['alias_target']:
                    f.write(f"  # {analysis['first_instruction']} {analysis['alias_target']}")
                elif analysis['sample_content']:
                    f.write(f"  # {analysis['sample_content'][0]}")
                f.write("\n")
        
        print(f"  Generated {config_file} with {len(alias_labels)} labels")
    
    def _generate_analysis_report(self, output_path: Path):
        """Generate detailed analysis report"""
        report_file = output_path / "listing_analysis_report.txt"
        
        with open(report_file, 'w') as f:
            f.write("CA65 Listing Analysis Report\n")
            f.write("=" * 50 + "\n\n")
            
            f.write(f"Input listing file: {self.listing_file}\n")
            f.write(f"Total listing lines: {len(self.lines)}\n")
            f.write(f"Parsed lines: {len(self.parsed_lines)}\n")
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
                    f.write(f"  Empty label: {analysis['is_empty_label']}\n")
                    
                    if analysis['alias_target']:
                        f.write(f"  Alias target: {analysis['alias_target']}\n")
                    
                    if analysis['sample_content']:
                        f.write(f"  Sample content:\n")
                        for content in analysis['sample_content'][:3]:
                            f.write(f"    {content}\n")
                
                f.write("\n")
        
        print(f"  Generated {report_file}")
    
    def _generate_usage_guide(self, output_path: Path):
        """Generate usage guide"""
        guide_file = output_path / "USAGE_GUIDE.txt"
        
        with open(guide_file, 'w') as f:
            f.write("CA65 Listing File Analyzer - Usage Guide\n")
            f.write("=" * 50 + "\n\n")
            
            f.write("OVERVIEW:\n")
            f.write("This analyzer parses ca65 listing files instead of raw assembly.\n")
            f.write("This is much more accurate because ca65 has already done the parsing!\n\n")
            
            f.write("HOW TO GENERATE LISTING FILE:\n")
            f.write("ca65 -l output.lst input.asm\n\n")
            
            f.write("THEN RUN ANALYZER:\n")
            f.write("python listing_analyzer.py output.lst [config_directory]\n\n")
            
            f.write("GENERATED FILES:\n")
            f.write("  code_labels.txt  - Labels for goto statements\n")
            f.write("  data_labels.txt  - Labels for data pointers\n")
            f.write("  alias_labels.txt - Simple label aliases\n")
            f.write("  listing_analysis_report.txt - Detailed analysis\n\n")
            
            f.write("ADVANTAGES OVER RAW ASSEMBLY PARSING:\n")
            f.write("- ca65 has already resolved all addresses and symbols\n")
            f.write("- Macro expansions are visible in listing\n")
            f.write("- Assembly directives are processed\n")
            f.write("- Much more reliable label detection\n")
            f.write("- Works with complex 65816 code\n\n")
            
            f.write("CLASSIFICATION LOGIC:\n")
            f.write("- DATA: Labels followed by .byte/.word/.res directives\n")
            f.write("- ALIAS: Labels with single jmp/jsr instruction\n") 
            f.write("- CODE: Labels followed by 6502/65816 instructions\n")
            f.write("- Empty labels use naming pattern analysis\n\n")
            
            f.write("EDITING THE RESULTS:\n")
            f.write("- Add # at start of line to comment out a label\n")
            f.write("- Move labels between files to change classification\n")
            f.write("- The analyzer is conservative - defaults to CODE when uncertain\n")
        
        print(f"  Generated {guide_file}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python listing_analyzer.py <listing_file> [output_directory]")
        print("")
        print("Arguments:")
        print("  listing_file      - Path to the ca65 listing file (.lst)")
        print("  output_directory  - Directory for config files (default: listing_config)")
        print("")
        print("First generate listing file with:")
        print("  ca65 -l output.lst input.asm")
        print("")
        print("Examples:")
        print("  python listing_analyzer.py duckhunt.lst")
        print("  python listing_analyzer.py duckhunt.lst my_config")
        sys.exit(1)
    
    listing_file = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else "listing_config"
    
    if not os.path.exists(listing_file):
        print(f"Error: Listing file '{listing_file}' not found")
        print("Generate it with: ca65 -l output.lst input.asm")
        sys.exit(1)
    
    try:
        # Create analyzer
        analyzer = CA65ListingAnalyzer(listing_file)
        
        # Analyze labels
        analyzer.analyze_labels()
        
        # Generate config files
        analyzer.generate_config_files(output_dir)
        
        print(f"\nDone! Check the '{output_dir}' directory for configuration files.")
        print("This analyzer used the ca65 listing file for much more accurate results!")
        print("Use these files with your 6502 translator.")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
