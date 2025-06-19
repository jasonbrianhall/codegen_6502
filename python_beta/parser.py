"""
Recursive Descent Parser for 6502 Assembly - FIXED VERSION
"""

from typing import List, Optional
from tokens import Token, TokenType
from ast_nodes import *

class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.pos = 0
        self.current_token = tokens[0] if tokens else None
    
    def debug_current_token(self, method_name: str):
        """Debug helper to show current parsing state"""
        if self.pos < len(self.tokens):
            token = self.tokens[self.pos]
            print(f"[DEBUG] {method_name}: pos={self.pos}, token='{token.value}' ({token.type.name}) line={token.line}")
        else:
            print(f"[DEBUG] {method_name}: pos={self.pos} (EOF)")

    def error(self, message: str):
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
        """Parse tokens into an AST"""
        print(f"Starting parse with {len(self.tokens)} tokens")
    
        root = RootNode()
        parsed_count = 0
    
        while not self.is_at_end():
            # Add debug output every 100 nodes
            if parsed_count % 100 == 0:
                self.debug_current_token(f"parse (node {parsed_count})")
        
            # Check for infinite loop protection
            start_pos = self.pos
        
            node = self.parse_top_level()
            if node:
                root.add_child(node)
                parsed_count += 1
        
            # Infinite loop protection
            if self.pos == start_pos and not self.is_at_end():
                self.debug_current_token("STUCK")
                print(f"ERROR: Parser stuck at position {self.pos}")
                print(f"Current token: {self.tokens[self.pos].value} ({self.tokens[self.pos].type.name})")    
                print(f"Next few tokens:")
                for i in range(min(5, len(self.tokens) - self.pos)):
                    t = self.tokens[self.pos + i]
                    print(f"  [{self.pos + i}] {t.value} ({t.type.name})")
                break
    
        print(f"Finished parsing. Created {parsed_count} nodes")
        return root    

    def parse_top_level(self):
        """Parse a top-level construct"""
        if self.pos >= len(self.tokens):
            return None
    
        token = self.tokens[self.pos]
    
        # Add debug for problematic tokens
        if token.type not in [TokenType.LABEL, TokenType.NAME, TokenType.DIRECTIVE, 
                             TokenType.LDA, TokenType.LDX, TokenType.LDY, TokenType.STA, 
                             TokenType.STX, TokenType.STY, TokenType.JMP, TokenType.JSR,
                             TokenType.RTS, TokenType.BEQ, TokenType.BNE, TokenType.DATABYTES,
                             TokenType.DATAWORDS, TokenType.EOF]:
            self.debug_current_token("parse_top_level (unexpected token)")
    
        if token.type == TokenType.LABEL:
            return self.parse_label()
        elif token.type == TokenType.NAME and self.peek_ahead() and self.peek_ahead().type == TokenType.EQUALS:
            return self.parse_declaration()
        elif token.type == TokenType.DIRECTIVE:
            if token.value in ['.db', '.byte']:
                return self.parse_data8()
            elif token.value in ['.dw', '.word']:
                return self.parse_data16()
            else:
                # Skip unknown directives
                self.advance()
                return None
        elif self.is_instruction():
            return self.parse_instruction()
        elif token.type == TokenType.EOF:
            return None
        else:
            # Skip unexpected tokens instead of getting stuck
            print(f"Skipping unexpected token: {token.value} ({token.type.name}) at line {token.line}")
            self.advance()
            return None


    def parse_directive(self):
        """Parse a directive (currently just consume it)"""
        self.advance()  # consume directive
        if self.current_token and self.current_token.type in [TokenType.HEXCONST, TokenType.BINCONST, TokenType.DECCONST]:
            self.advance()  # consume constant
    
    def parse_declaration(self) -> Optional[DeclNode]:
        """Parse a declaration: NAME '=' expr"""
        if not self.match(TokenType.NAME):
            return None
        
        name_token = self.current_token
        self.advance()
        
        if not self.match(TokenType.EQUALS):
            # This isn't a declaration, backtrack
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
        """Parse a section: LABEL code or LABEL section"""
        if not self.match(TokenType.LABEL):
            return None
        
        label_token = self.current_token
        self.advance()
        
        # Try to parse another section (nested labels)
        if self.match(TokenType.LABEL):
            child_section = self.parse_section()
            if child_section:
                label_node = LabelNode(label_token.value, child_section)
                label_node.line_number = label_token.line
                child_section.parent = label_node
                return label_node
        
        # Parse code block
        code = self.parse_code()
        if code:
            label_node = LabelNode(label_token.value, code)
            label_node.line_number = label_token.line
            code.parent = label_node
            return label_node
        
        self.error("Expected code or section after label")
    
    def parse_code(self) -> Optional[ListNode]:
        """Parse a code block (list of instructions and data) - FIXED VERSION"""
        items = []
        
        while (self.current_token and 
               self.current_token.type not in [TokenType.EOF, TokenType.LABEL]):
            
            # Try to parse instruction
            inst = self.parse_instruction()
            if inst:
                items.append(inst)
                continue
            
            # Try to parse data
            data = self.parse_data()
            if data:
                items.append(data)
                continue
            
            # If we can't parse either, break
            break
        
        if not items:
            return None
        
        # Create linked list in forward order - maintain source code order
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
        """Parse a comma-separated list of expressions - FIXED VERSION"""
        expressions = []
        
        expr = self.parse_expression()
        if not expr:
            return None
        
        expressions.append(expr)
        
        while self.match(TokenType.COMMA):
            self.advance()  # consume ','
            expr = self.parse_expression()
            if not expr:
                self.error("Expected expression after ','")
            expressions.append(expr)
        
        # Create linked list in forward order - maintain source code order
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
        
        # ASL/LSR/ROL/ROR can be with or without operand
        elif token.type in [TokenType.ASL, TokenType.LSR, TokenType.ROL, TokenType.ROR]:
            self.advance()
            operand = self.parse_instruction_expression()  # Optional
            inst = InstructionNode(token.type.value, operand)
            inst.line_number = token.line
            return inst
        
        # Branch instructions take NAME operands
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
        
    def is_at_end(self) -> bool:
        """Check if we're at the end of tokens"""
        return self.pos >= len(self.tokens) or (self.current_token and self.current_token.type == TokenType.EOF)

    def peek_ahead(self) -> Optional[Token]:
        """Look at the next token without advancing"""
        if self.pos + 1 < len(self.tokens):
            return self.tokens[self.pos + 1]
        return None

    def is_instruction(self) -> bool:
        """Check if current token is an instruction"""
        if not self.current_token:
            return False
    
        instruction_types = {
            TokenType.LDA, TokenType.LDX, TokenType.LDY,
            TokenType.STA, TokenType.STX, TokenType.STY,
            TokenType.TAX, TokenType.TAY, TokenType.TXA, TokenType.TYA,
            TokenType.TSX, TokenType.TXS, TokenType.PHA, TokenType.PHP,
            TokenType.PLA, TokenType.PLP, TokenType.AND, TokenType.EOR,
            TokenType.ORA, TokenType.BIT, TokenType.ADC, TokenType.SBC,
            TokenType.CMP, TokenType.CPX, TokenType.CPY, TokenType.INC,
            TokenType.INX, TokenType.INY, TokenType.DEC, TokenType.DEX,
            TokenType.DEY, TokenType.ASL, TokenType.LSR, TokenType.ROL,
            TokenType.ROR, TokenType.JMP, TokenType.JSR, TokenType.RTS,
            TokenType.BCC, TokenType.BCS, TokenType.BEQ, TokenType.BMI,
            TokenType.BNE, TokenType.BPL, TokenType.BVC, TokenType.BVS,
            TokenType.CLC, TokenType.CLD, TokenType.CLI, TokenType.CLV,
            TokenType.SEC, TokenType.SED, TokenType.SEI, TokenType.BRK,
            TokenType.NOP, TokenType.RTI
        }
    
        return self.current_token.type in instruction_types

    def parse_label(self) -> Optional[LabelNode]:
        """Parse a label and its content"""
        if not self.match(TokenType.LABEL):
            return None
    
        label_token = self.current_token
        self.advance()
    
        # Check for nested label
        if self.match(TokenType.LABEL):
            child_label = self.parse_label()
            if child_label:
                label_node = LabelNode(label_token.value, child_label)
                label_node.line_number = label_token.line
                child_label.parent = label_node
                return label_node
    
        # Parse code block
        code = self.parse_code()
        if code:
            label_node = LabelNode(label_token.value, code)
            label_node.line_number = label_token.line
            code.parent = label_node
            return label_node
    
        # Label with no content
        label_node = LabelNode(label_token.value, None)
        label_node.line_number = label_token.line
        return label_node

    def parse_data8(self) -> Optional[AstNode]:
        """Parse .db directive"""
        if not self.match(TokenType.DATABYTES):
            return None
    
        data_token = self.current_token
        self.advance()
    
        dlist = self.parse_data_list()
        if dlist:
            data_node = AstNode(AstType.AST_DATA8)
            data_node.line_number = data_token.line
            data_node.value = dlist
            dlist.parent = data_node
            return data_node
    
        return None

    def parse_data16(self) -> Optional[AstNode]:
        """Parse .dw directive"""
        if not self.match(TokenType.DATAWORDS):
            return None
    
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
