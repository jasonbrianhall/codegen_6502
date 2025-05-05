#!/usr/bin/env python3
"""
Python implementation of the 6502 assembler lexer
Converted from original asm6502.l flex file
"""

import ply.lex as lex
import os
import sys

# Import AST classes
from ast_classes import *
from util import map_comment, duplicate_string

# Dictionary for reserved words
reserved = {
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
    'slo': 'SLO',
    'brk': 'BRK',
    'nop': 'NOP',
    'rti': 'RTI',
    'dcp': 'DCP',
    'rla': 'RLA',
    'sre': 'SRE',
    'lax': 'LAX',
    'isc': 'ISC',
    'x': 'x',
    'y': 'y',
}

# List of token names
tokens = [
    'DATABYTES',
    'DATAWORDS',
    'DIRECTIVE',
    'LABEL',
    'NAME',
    'HEXCONST',
    'BINCONST',
    'DECCONST',
] + list(reserved.values())

# Simple tokens
literals = '=+-<>#,()'

# Regular expression rules for simple tokens

def t_DATABYTES(t):
    r'\.db'
    return t

def t_DATAWORDS(t):
    r'\.dw'
    return t

def t_DIRECTIVE(t):
    r'\.[a-z]+'
    t.value = duplicate_string(t.value)
    return t

def t_LABEL(t):
    r'[a-zA-Z]+[a-zA-Z0-9_]*:'
    t.value = duplicate_string(t.value)
    return t

def t_COMMENT(t):
    r';.*'
    map_comment(t.lineno, t.value)
    # No return, comments are ignored

def t_NAME(t):
    r'[a-zA-Z]+[a-zA-Z0-9_]*'
    # Check if it's a reserved word
    t.type = reserved.get(t.value, 'NAME')
    if t.type == 'NAME':
        t.value = duplicate_string(t.value)
    return t

def t_HEXCONST(t):
    r'\$[0-9A-Fa-f]+'
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

# Define a rule so we can track line numbers
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
