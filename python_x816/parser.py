"""
Recursive Descent Parser for 6502 Assembly - FIXED VERSION
"""

from typing import List, Optional
import re
from tokens import Token, TokenType
from ast_nodes import *

class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.pos = 0
        self.current_token = tokens[0] if tokens else None
        self.source_lines = []
        self.debug_mode = True
        
    def set_source_lines(self, lines: List[str]):
        """Set source lines for debugging purposes"""
        self.source_lines = lines
    
    def get_source_line(self, line_num: int) -> str:
        """Get the actual source line for debugging"""
        if self.source_lines and 1 <= line_num <= len(self.source_lines):
            return self.source_lines[line_num - 1].strip()
        return f"<line {line_num} not available>"
    
    def debug_print_token_context(self, message: str):
        """Print detailed debugging information about current token and context"""
        if not self.debug_mode:
            return
            
        print(f"\n=== PARSER DEBUG: {message} ===")
        
        if not self.current_token:
            print("Current token: None (EOF)")
            return
        
        print(f"Current token: {self.current_token.type.name} = '{self.current_token.value}'")
        print(f"Line {self.current_token.line}, Column {self.current_token.column}")
        print(f"Source line: {self.get_source_line(self.current_token.line)}")
        
        # Show a few tokens around the current position for context
        print(f"\nToken context (position {self.pos}):")
        start = max(0, self.pos - 2)
        end = min(len(self.tokens), self.pos + 3)
        
        for i in range(start, end):
            token = self.tokens[i]
            marker = " --> " if i == self.pos else "     "
            print(f"{marker}[{i}] {token.type.name}: '{token.value}' (line {token.line})")
        
        print("=" * 50)
    
    def error(self, message: str):
        self.debug_print_token_context(f"ERROR - {message}")
        if self.current_token:
            raise SyntaxError(f"Parse error at line {self.current_token.line}: {message}")
        else:
            raise SyntaxError(f"Parse error: {message}")
    
    def advance(self):
        """Move to the next token"""
        if self.pos < len(self.tokens) - 1:
            self.pos += 1
            self.current_token = self.tokens[self.pos]
        else:
            self.current_token = None
    
    def expect(self, token_type: TokenType) -> Token:
        """Expect a specific token type and advance"""
        if not self.current_token or self.current_token.type != token_type:
            self.error(f"Expected {token_type.name}, got {self.current_token.type.name if self.current_token else 'EOF'}")
        
        token = self.current_token
        self.advance()
        return token
    
    def match(self, token_type: TokenType) -> bool:
        """Check if current token matches type without advancing"""
        return self.current_token and self.current_token.type == token_type
    
    def parse(self) -> RootNode:
        """Main parsing entry point with comprehensive section recovery"""
        root = RootNode()
        labels_parsed = 0
        
        while self.current_token and self.current_token.type != TokenType.EOF:
            old_pos = self.pos
            
            try:
                # Handle directives
                if self.match(TokenType.DIRECTIVE):
                    self.parse_directive()
                    continue
                
                # Handle declarations (NAME = expr)
                elif self.match(TokenType.NAME):
                    decl = self.parse_declaration()
                    if decl:
                        root.children.append(decl)
                        decl.parent = root
                        continue
                    
                    # If not a declaration, check if it's a missed label
                    # Look ahead for colon
                    if (self.pos < len(self.tokens) - 1 and 
                        self.tokens[self.pos + 1].type == TokenType.LABEL):
                        # This is NAME followed by LABEL - skip NAME and parse LABEL
                        print(f"Skipping standalone NAME token: {self.current_token.value}")
                        self.advance()
                        continue
                    
                    # Unknown NAME - skip it
                    print(f"Skipping unknown NAME token: {self.current_token.value}")
                    self.advance()
                    continue
                
                # Handle labels - this is the main section parser
                elif self.match(TokenType.LABEL):
                    section = self.parse_section()
                    if section:
                        root.children.append(section)
                        section.parent = root
                        labels_parsed += 1
                        if self.debug_mode:
                            print(f"Parsed label #{labels_parsed}: {section.value} (line {section.line_number})")
                    continue
                
                else:
                    # Unknown token - skip it
                    if self.current_token:
                        if self.debug_mode:
                            print(f"Skipping unknown token: {self.current_token.type.name} '{self.current_token.value}'")
                    self.advance()
                    continue
                
            except Exception as e:
                print(f"Parse error at line {self.current_token.line if self.current_token else 'EOF'}: {e}")
                
                # Recovery: skip to next label or EOF
                while (self.current_token and 
                       self.current_token.type not in [TokenType.LABEL, TokenType.EOF]):
                    self.advance()
                continue
            
            # Ensure we're making progress
            if self.pos == old_pos and self.current_token:
                print(f"Forcing advance to prevent infinite loop at token: {self.current_token.type.name}")
                self.advance()
        
        print(f"Parser completed: {len(root.children)} root children, {labels_parsed} labels")
        return root
    
    def parse_directive(self):
        """Parse a directive"""
        directive_token = self.current_token
        self.advance()
        
        # Consume any following constant
        if self.current_token and self.current_token.type in [TokenType.HEXCONST, TokenType.BINCONST, TokenType.DECCONST]:
            self.advance()
    
    def parse_declaration(self) -> Optional[DeclNode]:
        """Parse a declaration: NAME '=' expr"""
        if not self.match(TokenType.NAME):
            return None
        
        name_token = self.current_token
        self.advance()
        
        if not self.match(TokenType.EQUALS):
            # Not a declaration - backtrack
            self.pos -= 1
            self.current_token = self.tokens[self.pos]
            return None
        
        self.advance()  # consume '='
        
        expr = self.parse_expression()
        if not expr:
            self.error("Expected expression after '='")
        
        decl = DeclNode(name_token.value, expr)
        decl.line_number = name_token.line
        return decl
    
    def parse_section(self) -> Optional[LabelNode]:
        """Parse a complete label section"""
        if not self.match(TokenType.LABEL):
            return None
        
        label_token = self.current_token
        self.advance()
        
        # Parse the content after this label
        content = self.parse_label_content()
        
        label_node = LabelNode(label_token.value, content)
        label_node.line_number = label_token.line
        
        if content:
            content.parent = label_node
        
        return label_node
    
    def parse_label_content(self) -> Optional[ListNode]:
        """Parse everything after a label until we hit another label or EOF"""
        items = []
        items_parsed = 0
        
        while (self.current_token and 
               self.current_token.type not in [TokenType.EOF, TokenType.LABEL]):
            
            old_pos = self.pos
            item = None
            
            try:
                # Try to parse instruction
                if self.current_token.type in [
                    TokenType.LDA, TokenType.LDX, TokenType.LDY, TokenType.STA, TokenType.STX, TokenType.STY,
                    TokenType.TAX, TokenType.TAY, TokenType.TXA, TokenType.TYA, TokenType.TSX, TokenType.TXS,
                    TokenType.PHA, TokenType.PHP, TokenType.PLA, TokenType.PLP, TokenType.AND, TokenType.EOR,
                    TokenType.ORA, TokenType.BIT, TokenType.ADC, TokenType.SBC, TokenType.CMP, TokenType.CPX,
                    TokenType.CPY, TokenType.INC, TokenType.INX, TokenType.INY, TokenType.DEC, TokenType.DEX,
                    TokenType.DEY, TokenType.ASL, TokenType.LSR, TokenType.ROL, TokenType.ROR, TokenType.JMP,
                    TokenType.JSR, TokenType.RTS, TokenType.BCC, TokenType.BCS, TokenType.BEQ, TokenType.BMI,
                    TokenType.BNE, TokenType.BPL, TokenType.BVC, TokenType.BVS, TokenType.CLC, TokenType.CLD,
                    TokenType.CLI, TokenType.CLV, TokenType.SEC, TokenType.SED, TokenType.SEI, TokenType.BRK,
                    TokenType.NOP, TokenType.RTI
                ]:
                    item = self.parse_instruction()
                
                # Try to parse data
                elif self.current_token.type in [TokenType.DATABYTES, TokenType.DATAWORDS]:
                    item = self.parse_data()
                
                else:
                    # Unknown token in label content - skip it
                    if self.debug_mode:
                        print(f"    Skipping unknown token in label content: {self.current_token.type.name}")
                    self.advance()
                    continue
                
                if item:
                    items.append(item)
                    items_parsed += 1
                    
                    if self.debug_mode and items_parsed % 50 == 0:
                        print(f"      Parsed {items_parsed} items in current label...")
                
            except Exception as e:
                print(f"Error parsing label content: {e}")
                # Skip this token and continue
                if self.pos == old_pos:
                    self.advance()
                continue
            
            # Ensure we made progress
            if self.pos == old_pos:
                if self.current_token:
                    self.advance()
                break
        
        if not items:
            return None
        
        # Create linked list in forward order (preserving source order)
        head = None
        tail = None
        
        for item in items:
            list_node = ListNode()
            list_node.value = item
            item.parent = list_node
            list_node.next = None
            
            if head is None:
                head = list_node
                tail = list_node
            else:
                tail.next = list_node
                tail = list_node
        
        return head
    
    def parse_instruction(self) -> Optional[InstructionNode]:
        """Parse a 6502 instruction"""
        if not self.current_token:
            return None
        
        token = self.current_token
        
        # Instructions that take operands
        if token.type in [TokenType.LDA, TokenType.LDX, TokenType.LDY, 
                         TokenType.STA, TokenType.STX, TokenType.STY,
                         TokenType.AND, TokenType.EOR, TokenType.ORA, TokenType.BIT,
                         TokenType.ADC, TokenType.SBC, TokenType.CMP, TokenType.CPX, TokenType.CPY,
                         TokenType.INC, TokenType.DEC, TokenType.JMP]:
            self.advance()
            operand = self.parse_instruction_expression()
            inst = InstructionNode(token.type.value, operand)
            inst.line_number = token.line
            return inst
        
        # Shift instructions (can be with or without operand)
        elif token.type in [TokenType.ASL, TokenType.LSR, TokenType.ROL, TokenType.ROR]:
            self.advance()
            operand = self.parse_instruction_expression()  # Optional
            inst = InstructionNode(token.type.value, operand)
            inst.line_number = token.line
            return inst
        
        # Branch/jump instructions that take NAME operands
        elif token.type in [TokenType.JSR, TokenType.BCC, TokenType.BCS, TokenType.BEQ, 
                           TokenType.BMI, TokenType.BNE, TokenType.BPL, TokenType.BVC, TokenType.BVS]:
            self.advance()
            if not self.match(TokenType.NAME):
                self.error(f"Expected NAME after {token.type.name}")
            name_token = self.current_token
            self.advance()
            inst = InstructionNode(token.type.value, name_token.value)
            inst.line_number = token.line
            return inst
        
        # Instructions with no operands
        elif token.type in [TokenType.TAX, TokenType.TAY, TokenType.TXA, TokenType.TYA,
                           TokenType.TSX, TokenType.TXS, TokenType.PHA, TokenType.PHP,
                           TokenType.PLA, TokenType.PLP, TokenType.INX, TokenType.INY,
                           TokenType.DEX, TokenType.DEY, TokenType.RTS, TokenType.CLC,
                           TokenType.CLD, TokenType.CLI, TokenType.CLV, TokenType.SEC,
                           TokenType.SED, TokenType.SEI, TokenType.BRK, TokenType.NOP, TokenType.RTI]:
            self.advance()
            inst = InstructionNode(token.type.value, None)
            inst.line_number = token.line
            return inst
        
        return None
    
    def parse_data(self) -> Optional[AstNode]:
        """Parse data declaration: .db or .dw followed by data list"""
        if self.match(TokenType.DATABYTES):
            data_token = self.current_token
            self.advance()
            dlist = self.parse_data_list()
            if dlist:
                data_node = AstNode(AstType.AST_DATA8)
                data_node.line_number = data_token.line
                data_node.value = dlist
                dlist.parent = data_node
                return data_node
        elif self.match(TokenType.DATAWORDS):
            data_token = self.current_token
            self.advance()
            dlist = self.parse_data_list()
            if dlist:
                data_node = AstNode(AstType.AST_DATA16)
                data_node.line_number = data_token.line
                data_node.value = dlist
                dlist.parent = data_node
                return data_node
        
        return None
    
    def parse_data_list(self) -> Optional[ListNode]:
        """Parse a comma-separated list of expressions"""
        expressions = []
        
        expr = self.parse_expression()
        if not expr:
            return None
        
        expressions.append(expr)
        
        while self.match(TokenType.COMMA):
            self.advance()  # consume ','
            expr = self.parse_expression()
            if not expr:
                break
            expressions.append(expr)
        
        # Create linked list in forward order
        head = None
        tail = None
        
        for expr in expressions:
            list_node = ListNode()
            list_node.value = expr
            expr.parent = list_node
            list_node.next = None
            
            if head is None:
                head = list_node
                tail = list_node
            else:
                tail.next = list_node
                tail = list_node
        
        return head
    
    def parse_expression(self) -> Optional[AstNode]:
        """Parse an expression"""
        return self.parse_additive_expression()
    
    def parse_additive_expression(self) -> Optional[AstNode]:
        """Parse addition and subtraction"""
        left = self.parse_primary_expression()
        if not left:
            return None
        
        while self.current_token and self.current_token.type in [TokenType.PLUS, TokenType.MINUS]:
            op_token = self.current_token
            self.advance()
            right = self.parse_primary_expression()
            if not right:
                self.error(f"Expected expression after '{op_token.value}'")
            
            if op_token.type == TokenType.PLUS:
                left = BinaryNode(AstType.AST_ADD, left, right)
            else:
                left = BinaryNode(AstType.AST_SUBTRACT, left, right)
        
        return left
    
    def parse_primary_expression(self) -> Optional[AstNode]:
        """Parse primary expressions"""
        if self.match(TokenType.NAME):
            name_token = self.current_token
            self.advance()
            return AstNode(AstType.AST_NAME, name_token.value)
        
        const = self.parse_const()
        if const:
            return AstNode(AstType.AST_CONST, const)
        
        if self.match(TokenType.HASH):
            self.advance()  # consume '#'
            expr = self.parse_expression()
            if not expr:
                self.error("Expected expression after '#'")
            return UnaryNode(AstType.AST_IMMEDIATE, expr)
        
        if self.match(TokenType.LESS):
            self.advance()  # consume '<'
            expr = self.parse_expression()
            if not expr:
                self.error("Expected expression after '<'")
            return UnaryNode(AstType.AST_LOBYTE, expr)
        
        if self.match(TokenType.GREATER):
            self.advance()  # consume '>'
            expr = self.parse_expression()
            if not expr:
                self.error("Expected expression after '>'")
            return UnaryNode(AstType.AST_HIBYTE, expr)
        
        if self.match(TokenType.LPAREN):
            self.advance()  # consume '('
            expr = self.parse_expression()
            if not expr:
                self.error("Expected expression after '('")
            self.expect(TokenType.RPAREN)
            return UnaryNode(AstType.AST_INDIRECT, expr)
        
        return None
    
    def parse_instruction_expression(self) -> Optional[AstNode]:
        """Parse instruction operand expression (can have indexing)"""
        expr = self.parse_expression()
        if not expr:
            return None
        
        # Check for indexing
        if self.match(TokenType.COMMA):
            self.advance()  # consume ','
            if self.match(TokenType.X_REG):
                self.advance()
                return UnaryNode(AstType.AST_INDEXED_X, expr)
            elif self.match(TokenType.Y_REG):
                self.advance()
                return UnaryNode(AstType.AST_INDEXED_Y, expr)
            else:
                self.error("Expected 'x' or 'y' after ','")
        
        return expr
    
    def parse_const(self) -> Optional[str]:
        """Parse a constant (hex, binary, or decimal)"""
        if self.match(TokenType.HEXCONST):
            value = self.current_token.value
            self.advance()
            return value
        elif self.match(TokenType.BINCONST):
            value = self.current_token.value
            self.advance()
            return value
        elif self.match(TokenType.DECCONST):
            value = self.current_token.value
            self.advance()
            return value
        return None
