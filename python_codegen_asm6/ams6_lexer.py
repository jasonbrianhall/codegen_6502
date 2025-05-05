#!/usr/bin/env python3
"""
Python implementation of the asm6 lexer
Based on the original asm6502 lexer but modified for asm6 syntax
"""

import ply.lex as lex
import os
import sys

# Import AST classes and utilities
from ast_classes import *
from util import map_comment, duplicate_string

# Dictionary for reserved words
reserved = {
    # Standard 6502 opcodes
    'lda': 'LDA',
    'ldx': 'LDX',
    'ldy': 'LDY',
    'sta': 'STA',
    'stx': 'STX',
    'sty': 'STY',
    'tax': 'TAX',
    'tay': 'TAY',
    'txa': 'TXA',
    'tya': 'TYA',
    'tsx': 'TSX',
    'txs': 'TXS',
    'pha': 'PHA',
    'php': 'PHP',
    'pla': 'PLA',
    'plp': 'PLP',
    'and': 'AND',
    'eor': 'EOR',
    'ora': 'ORA',
    'bit': 'BIT',
    'adc': 'ADC',
    'sbc': 'SBC',
    'cmp': 'CMP',
    'cpx': 'CPX',
    'cpy': 'CPY',
    'inc': 'INC',
    'inx': 'INX',
    'iny': 'INY',
    'dec': 'DEC',
    'dex': 'DEX',
    'dey': 'DEY',
    'asl': 'ASL',
    'lsr': 'LSR',
    'rol': 'ROL',
    'ror': 'ROR',
    'jmp': 'JMP',
    'jsr': 'JSR',
    'rts': 'RTS',
    'bcc': 'BCC',
    'bcs': 'BCS',
    'beq': 'BEQ',
    'bmi': 'BMI',
    'bne': 'BNE',
    'bpl': 'BPL',
    'bvc': 'BVC',
    'bvs': 'BVS',
    'clc': 'CLC',
    'cld': 'CLD',
    'cli': 'CLI',
    'clv': 'CLV',
    'sec': 'SEC',
    'sed': 'SED',
    'sei': 'SEI',
    'brk': 'BRK',
    'nop': 'NOP',
    'rti': 'RTI',
    'x': 'X',
    'y': 'Y',
    
    # asm6-specific directives
    'db': 'DATABYTES',  # db instead of .db
    'dw': 'DATAWORDS',  # dw instead of .dw
    'org': 'ORG',       # org directive
    'equ': 'EQU',       # equ directive
    'incbin': 'INCBIN', # include binary file
    'include': 'INCLUDE', # include source file
    'if': 'IF',         # conditional assembly
    'endif': 'ENDIF',   # end conditional assembly
    'ifdef': 'IFDEF',   # check if defined
    'ifndef': 'IFNDEF', # check if not defined
    'else': 'ELSE',     # else clause for conditionals
    'macro': 'MACRO',   # macro definition
    'endm': 'ENDM',     # end macro definition
    'bank': 'BANK',     # bank switching
    'base': 'BASE',     # set base address for relocatable code
    'pad': 'PAD',       # pad to specific address
    'align': 'ALIGN',   # align to specific boundary
    'fillvalue': 'FILLVALUE', # value to use for padding
    'dsb': 'DSB',       # define storage bytes
    'dsw': 'DSW',       # define storage words
    'rs': 'RS',         # reserve space (for RAM variables)
    'enum': 'ENUM',     # enumeration
    'ende': 'ENDE',     # end enumeration
}

# List of token names, including asm6-specific ones
tokens = [
    'LABEL',
    'NAME',
    'HEXCONST',
    'BINCONST',
    'DECCONST',
    'STRING',
    'DIRECTIVE',
    'LOCAL_LABEL',
    'CURRENT_ADDR',
] + list(reserved.values())

# Simple tokens
literals = '=+-<>*/#,()[]:|&^%!'

# Regular expression rules for tokens

def t_LOCAL_LABEL(t):
    r'\.[a-zA-Z_][a-zA-Z0-9_]*'
    t.value = duplicate_string(t.value)
    return t

def t_LABEL(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*:'
    t.value = duplicate_string(t.value)
    return t

def t_COMMENT(t):
    r';.*|//.*'  # Support both ; and // for comments
    map_comment(t.lineno, t.value)
    # No return, comments are ignored

def t_STRING(t):
    r'"[^"]*"'
    t.value = duplicate_string(t.value)
    return t

def t_CURRENT_ADDR(t):
    r'\*'  # Current address symbol
    t.value = duplicate_string(t.value)
    return t

def t_HEXCONST(t):
    r'\$[0-9A-Fa-f]+|0x[0-9A-Fa-f]+'  # Support both $FF and 0xFF
    t.value = duplicate_string(t.value)
    return t

def t_BINCONST(t):
    r'%[0|1]+'
    t.value = duplicate_string(t.value)
    return t

def t_DECCONST(t):
    r'[0-9]+'
    t.value = duplicate_string(t.value)
    return t

def t_NAME(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    # Check if it's a reserved word
    t.type = reserved.get(t.value.lower(), 'NAME')
    if t.type == 'NAME':
        t.value = duplicate_string(t.value)
    return t

def t_DIRECTIVE(t):
    r'\.[a-zA-Z][a-zA-Z0-9_]*'
    # Check if it's a predefined directive
    directive_name = t.value[1:].lower()  # Remove the dot and convert to lowercase
    if directive_name in reserved:
        t.type = reserved[directive_name]
    else:
        t.value = duplicate_string(t.value)
    return t

# Define a rule to track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# A string containing ignored characters (spaces and tabs)
t_ignore = ' \t\r'

# Error handling rule
def t_error(t):
    print(f"invalid token (line {t.lineno}): {t.value[0]}")
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()
