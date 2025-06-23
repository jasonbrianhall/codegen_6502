"""
Fixed Lexical Analyzer for 6502 Assembly with proper CA65 support
"""

import re
from typing import List, Optional, Iterator
from tokens import Token, TokenType, INSTRUCTION_MAP
from util import map_comment

class Lexer:
    def __init__(self, text: str):
        self.text = text
        self.pos = 0
        self.line = 1
        self.column = 1
        self.tokens: List[Token] = []
        
    def read_string(self) -> str:
        """Read a quoted string"""
        quote_char = self.advance()  # consume opening quote
        string_val = quote_char  # include the quote in the token
    
        while self.pos < len(self.text) and self.text[self.pos] != quote_char:
            if self.text[self.pos] == '\\':
                # Handle escape sequences
                string_val += self.advance()  # consume backslash
                if self.pos < len(self.text):
                    string_val += self.advance()  # consume escaped character
            else:
                string_val += self.advance()
    
        if self.pos < len(self.text):
            string_val += self.advance()  # consume closing quote
    
        return string_val

    def error(self, message: str):
        raise ValueError(f"Lexical error at line {self.line}, column {self.column}: {message}")
    
    def peek(self, offset: int = 0) -> str:
        """Peek at character at current position + offset"""
        pos = self.pos + offset
        if pos >= len(self.text):
            return ''
        return self.text[pos]
    
    def advance(self) -> str:
        """Advance position and return current character"""
        if self.pos >= len(self.text):
            return ''
        
        char = self.text[self.pos]
        self.pos += 1
        
        if char == '\n':
            self.line += 1
            self.column = 1
        else:
            self.column += 1
        
        return char
    
    def skip_whitespace(self):
        """Skip whitespace characters"""
        while self.pos < len(self.text) and self.text[self.pos] in ' \t\r\n':
            self.advance()
    
    def read_comment(self) -> str:
        """Read a comment starting with ';'"""
        comment = ""
        while self.pos < len(self.text) and self.text[self.pos] != '\n':
            comment += self.advance()
        return comment
    
    def read_directive(self) -> str:
        """Read a directive starting with '.'"""
        directive = ""
        while (self.pos < len(self.text) and 
               (self.text[self.pos].isalpha() or self.text[self.pos] == '.')):
            directive += self.advance()
        return directive
    
    def read_name_with_addressing(self) -> tuple:
        """Read a name, handling CA65 addressing mode directives"""
        addressing_mode = ""
        name = ""
        
        # Check for CA65 addressing mode prefixes (z: or a:)
        if self.pos < len(self.text) - 1:
            if self.text[self.pos] in 'za' and self.text[self.pos + 1] == ':':
                addressing_mode = self.advance() + self.advance()  # consume "z:" or "a:"
        
        # Read the actual name
        while (self.pos < len(self.text) and 
               (self.text[self.pos].isalnum() or self.text[self.pos] in '_')):
            name += self.advance()
        
        return addressing_mode, name
    
    def read_hex_constant(self) -> str:
        """Read a hexadecimal constant starting with '$'"""
        const = self.advance()  # consume '$'
        while (self.pos < len(self.text) and 
               self.text[self.pos] in '0123456789ABCDEFabcdef'):
            const += self.advance()
        return const
    
    def read_bin_constant(self) -> str:
        """Read a binary constant starting with '%'"""
        const = self.advance()  # consume '%'
        while (self.pos < len(self.text) and 
               self.text[self.pos] in '01'):
            const += self.advance()
        return const
    
    def read_dec_constant(self) -> str:
        """Read a decimal constant"""
        const = ""
        while (self.pos < len(self.text) and 
               self.text[self.pos].isdigit()):
            const += self.advance()
        return const
    
    def tokenize(self) -> List[Token]:
        """Tokenize the input text with improved CA65 support"""
        while self.pos < len(self.text):
            # Skip whitespace
            if self.text[self.pos] in ' \t\r\n':
                self.skip_whitespace()
                continue
        
            current_line = self.line
            current_column = self.column
        
            # Comments
            if self.text[self.pos] == ';':
                comment = self.read_comment()
                map_comment(current_line, comment)
                continue
        
            # Directives
            if self.text[self.pos] == '.':
                directive = self.read_directive()
                if directive == '.db' or directive == '.byte':
                    self.tokens.append(Token(TokenType.DATABYTES, directive, current_line, current_column))
                elif directive == '.dw' or directive == '.word':
                    self.tokens.append(Token(TokenType.DATAWORDS, directive, current_line, current_column))
                else:
                    self.tokens.append(Token(TokenType.DIRECTIVE, directive, current_line, current_column))
                continue
        
            # Hexadecimal constants
            if self.text[self.pos] == '$':
                hex_const = self.read_hex_constant()    
                self.tokens.append(Token(TokenType.HEXCONST, hex_const, current_line, current_column))
                continue
        
            # Binary constants
            if self.text[self.pos] == '%':
                bin_const = self.read_bin_constant()
                self.tokens.append(Token(TokenType.BINCONST, bin_const, current_line, current_column))
                continue
        
            # String literals (CA65 format)
            if self.text[self.pos] in '"\'':
                string_literal = self.read_string()
                self.tokens.append(Token(TokenType.NAME, string_literal, current_line, current_column))
                continue
        
            # Decimal constants
            if self.text[self.pos].isdigit():
                dec_const = self.read_dec_constant()
                self.tokens.append(Token(TokenType.DECCONST, dec_const, current_line, current_column))
                continue
        
            # Single character tokens
            char = self.text[self.pos]
            if char == '=':
                self.advance()
                self.tokens.append(Token(TokenType.EQUALS, char, current_line, current_column))
                continue
            elif char == ',':
                self.advance()
                self.tokens.append(Token(TokenType.COMMA, char, current_line, current_column))
                continue
            elif char == '#':
                self.advance()
                self.tokens.append(Token(TokenType.HASH, char, current_line, current_column))
                continue
            elif char == '+':
                self.advance()
                self.tokens.append(Token(TokenType.PLUS, char, current_line, current_column))
                continue
            elif char == '-':
                self.advance()
                self.tokens.append(Token(TokenType.MINUS, char, current_line, current_column))
                continue
            elif char == '<':
                self.advance()
                self.tokens.append(Token(TokenType.LESS, char, current_line, current_column))
                continue
            elif char == '>':
                self.advance()
                self.tokens.append(Token(TokenType.GREATER, char, current_line, current_column))
                continue
            elif char == '(':
                self.advance()
                self.tokens.append(Token(TokenType.LPAREN, char, current_line, current_column))
                continue
            elif char == ')':
                self.advance()
                self.tokens.append(Token(TokenType.RPAREN, char, current_line, current_column))
                continue
        
            # Names, labels, instructions, and registers with CA65 addressing modes
            if char.isalpha() or char == '_':
                addressing_mode, name = self.read_name_with_addressing()
                
                # Skip empty names (from pure addressing modes)
                if not name:
                    continue
                
                # Combine addressing mode with name for processing
                full_name = addressing_mode + name if addressing_mode else name
            
                # Check if it continues with ':' for labels
                if self.pos < len(self.text) and self.text[self.pos] == ':':
                    colon = self.advance()  # consume ':'
                    label = full_name + colon
                    self.tokens.append(Token(TokenType.LABEL, label, current_line, current_column))
                    continue

                # Check for special register names
                if name == 'x':
                    self.tokens.append(Token(TokenType.X_REG, name, current_line, current_column))
                    continue
                elif name == 'y':
                    self.tokens.append(Token(TokenType.Y_REG, name, current_line, current_column))
                    continue
            
                # Check for instructions (without addressing mode prefix for matching)
                if name.lower() in INSTRUCTION_MAP:
                    token_type = INSTRUCTION_MAP[name.lower()]
                    self.tokens.append(Token(token_type, name, current_line, current_column))
                    continue
            
                # Otherwise it's a name (include addressing mode)
                self.tokens.append(Token(TokenType.NAME, full_name, current_line, current_column))
                continue
        
            # If we get here, it's an invalid character
            self.error(f"Invalid character: '{char}'")
    
        # Add EOF token
        self.tokens.append(Token(TokenType.EOF, "", self.line, self.column))
        return self.tokens
