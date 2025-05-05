#!/usr/bin/env python3
"""
Python implementation of the asm6 parser
Based on the original asm6502 parser but modified for asm6 syntax
"""

import os
import sys
import ply.yacc as yacc

# Get the token map from the lexer
from asm6_lexer import tokens
from ast_classes import *
from util import lookup_comment

# Global root node
root = None

# Helper macro for instruction node creation
def INST(lineno, code, operand):
    node = InstructionNode(code, operand)
    node.line_number = lineno
    return node

# Start symbol
def p_program(p):
    'program : plist'
    pass

def p_plist_dir(p):
    'plist : dir'
    pass

def p_plist_decl(p):
    'plist : decl'
    global root
    root.children.append(p[1])
    p[1].parent = root

def p_plist_section(p):
    'plist : section'
    global root
    root.children.append(p[1])
    p[1].parent = root

def p_plist_plist_dir(p):
    'plist : plist dir'
    pass

def p_plist_plist_decl(p):
    'plist : plist decl'
    global root
    root.children.append(p[2])
    p[2].parent = root

def p_plist_plist_section(p):
    'plist : plist section'
    global root
    root.children.append(p[2])
    p[2].parent = root

# Modified to support asm6 directives
def p_dir(p):
    '''dir : ORG expr
           | DIRECTIVE expr
           | INCBIN STRING
           | INCLUDE STRING
           | IF expr
           | IFDEF NAME
           | IFNDEF NAME
           | ELSE
           | ENDIF
           | MACRO NAME
           | ENDM
           | BANK expr
           | BASE expr
           | PAD expr
           | ALIGN expr
           | FILLVALUE expr
           | DSB expr
           | DSB expr "," expr
           | DSW expr
           | RS expr
           | ENUM expr
           | ENDE'''
    # We ignore directives for now, as they're primarily used during assembly
    # But we'll want to handle them properly in a full implementation
    pass

# Modified to support asm6 syntax for declarations
def p_decl(p):
    '''decl : NAME "=" expr
            | NAME EQU expr'''
    p[0] = DeclNode(p[1], p[3])
    p[0].line_number = p.lineno(1)

def p_section_label_code(p):
    'section : LABEL code'
    label_name = p[1]
    if label_name.endswith(':'):
        label_name = label_name[:-1]  # Remove the trailing colon
    p[0] = LabelNode(label_name + ':', p[2])  # Add colon back for compatibility
    p[0].line_number = p.lineno(1)
    p[2].parent = p[0]

def p_section_label_section(p):
    'section : LABEL section'
    label_name = p[1]
    if label_name.endswith(':'):
        label_name = label_name[:-1]  # Remove the trailing colon
    p[0] = LabelNode(label_name + ':', p[2])  # Add colon back for compatibility
    p[2].parent = p[0]

def p_code_inst(p):
    'code : inst'
    p[0] = ListNode()
    p[0].value.node = p[1]
    p[1].parent = p[0]

def p_code_data(p):
    'code : data'
    p[0] = ListNode()
    p[0].value.node = p[1]
    p[1].parent = p[0]

def p_code_code_inst(p):
    'code : code inst'
    p[0] = ListNode()
    p[0].value.node = p[2]
    p[2].parent = p[0]
    p[0].next = p[1]

def p_code_code_data(p):
    'code : code data'
    p[0] = ListNode()
    p[0].value.node = p[2]
    p[2].parent = p[0]
    p[0].next = p[1]

# Modified for asm6 syntax
def p_data_databytes(p):
    '''data : DATABYTES dlist
            | db dlist'''
    p[0] = AstNode(AstType.AST_DATA8)
    p[0].line_number = p.lineno(1)
    p[0].value.node = p[2]
    p[2].parent = p[0]

def p_data_datawords(p):
    '''data : DATAWORDS dlist
            | dw dlist'''
    p[0] = AstNode(AstType.AST_DATA16)
    p[0].line_number = p.lineno(1)
    p[0].value.node = p[2]
    p[2].parent = p[0]

def p_dlist_expr(p):
    'dlist : expr'
    p[0] = ListNode()
    p[0].value.node = p[1]
    p[1].parent = p[0]

def p_dlist_string(p):
    'dlist : STRING'
    # Create a list node for the string
    p[0] = ListNode()
    
    # Remove the quotes from the string
    string_value = p[1][1:-1]
    
    # Create a constant node for each character in the string
    current_node = p[0]
    for i, char in enumerate(string_value):
        node = AstNode(AstType.AST_CONST, str(ord(char)))
        
        if i == 0:
            # First character
            current_node.value.node = node
            node.parent = current_node
        else:
            # Subsequent characters
            next_node = ListNode()
            next_node.value.node = node
            node.parent = next_node
            current_node.next = next_node
            current_node = next_node

def p_dlist_dlist_expr(p):
    'dlist : dlist "," expr'
    p[0] = ListNode()
    p[0].value.node = p[3]
    p[3].parent = p[0]
    p[0].next = p[1]

def p_dlist_dlist_string(p):
    'dlist : dlist "," STRING'
    # Create a list node for the next part
    p[0] = ListNode()
    
    # Remove the quotes from the string
    string_value = p[3][1:-1]
    
    # Create a constant node for each character in the string
    current_node = p[0]
    for i, char in enumerate(string_value):
        node = AstNode(AstType.AST_CONST, str(ord(char)))
        
        if i == 0:
            # First character
            current_node.value.node = node
            node.parent = current_node
        else:
            # Subsequent characters
            next_node = ListNode()
            next_node.value.node = node
            node.parent = next_node
            current_node.next = next_node
            current_node = next_node
            
    # Link to the rest of the list
    if current_node != p[0]:
        current_node.next = p[1]
    else:
        p[0].next = p[1]

# All the instruction definitions
def p_inst_lda(p):
    'inst : LDA iexpr'
    p[0] = INST(p.lineno(1), LDA, p[2])

def p_inst_ldx(p):
    'inst : LDX iexpr'
    p[0] = INST(p.lineno(1), LDX, p[2])

def p_inst_ldy(p):
    'inst : LDY iexpr'
    p[0] = INST(p.lineno(1), LDY, p[2])

def p_inst_sta(p):
    'inst : STA iexpr'
    p[0] = INST(p.lineno(1), STA, p[2])

def p_inst_stx(p):
    'inst : STX iexpr'
    p[0] = INST(p.lineno(1), STX, p[2])

def p_inst_sty(p):
    'inst : STY iexpr'
    p[0] = INST(p.lineno(1), STY, p[2])

def p_inst_tax(p):
    'inst : TAX'
    p[0] = INST(p.lineno(1), TAX, None)

def p_inst_tay(p):
    'inst : TAY'
    p[0] = INST(p.lineno(1), TAY, None)

def p_inst_txa(p):
    'inst : TXA'
    p[0] = INST(p.lineno(1), TXA, None)

def p_inst_tya(p):
    'inst : TYA'
    p[0] = INST(p.lineno(1), TYA, None)

def p_inst_tsx(p):
    'inst : TSX'
    p[0] = INST(p.lineno(1), TSX, None)

def p_inst_txs(p):
    'inst : TXS'
    p[0] = INST(p.lineno(1), TXS, None)

def p_inst_pha(p):
    'inst : PHA'
    p[0] = INST(p.lineno(1), PHA, None)

def p_inst_php(p):
    'inst : PHP'
    p[0] = INST(p.lineno(1), PHP, None)

def p_inst_pla(p):
    'inst : PLA'
    p[0] = INST(p.lineno(1), PLA, None)

def p_inst_plp(p):
    'inst : PLP'
    p[0] = INST(p.lineno(1), PLP, None)

def p_inst_and(p):
    'inst : AND iexpr'
    p[0] = INST(p.lineno(1), AND, p[2])

def p_inst_eor(p):
    'inst : EOR iexpr'
    p[0] = INST(p.lineno(1), EOR, p[2])

def p_inst_ora(p):
    'inst : ORA iexpr'
    p[0] = INST(p.lineno(1), ORA, p[2])

def p_inst_bit(p):
    'inst : BIT iexpr'
    p[0] = INST(p.lineno(1), BIT, p[2])

def p_inst_adc(p):
    'inst : ADC iexpr'
    p[0] = INST(p.lineno(1), ADC, p[2])

def p_inst_sbc(p):
    'inst : SBC iexpr'
    p[0] = INST(p.lineno(1), SBC, p[2])

def p_inst_cmp(p):
    'inst : CMP iexpr'
    p[0] = INST(p.lineno(1), CMP, p[2])

def p_inst_cpx(p):
    'inst : CPX iexpr'
    p[0] = INST(p.lineno(1), CPX, p[2])

def p_inst_cpy(p):
    'inst : CPY iexpr'
    p[0] = INST(p.lineno(1), CPY, p[2])

def p_inst_inc(p):
    'inst : INC iexpr'
    p[0] = INST(p.lineno(1), INC, p[2])

def p_inst_inx(p):
    'inst : INX'
    p[0] = INST(p.lineno(1), INX, None)

def p_inst_iny(p):
    'inst : INY'
    p[0] = INST(p.lineno(1), INY, None)

def p_inst_dec(p):
    'inst : DEC iexpr'
    p[0] = INST(p.lineno(1), DEC, p[2])

def p_inst_dex(p):
    'inst : DEX'
    p[0] = INST(p.lineno(1), DEX, None)

def p_inst_dey(p):
    'inst : DEY'
    p[0] = INST(p.lineno(1), DEY, None)

def p_inst_asl(p):
    'inst : ASL'
    p[0] = INST(p.lineno(1), ASL, None)

def p_inst_asl_iexpr(p):
    'inst : ASL iexpr'
    p[0] = INST(p.lineno(1), ASL, p[2])

def p_inst_lsr(p):
    'inst : LSR'
    p[0] = INST(p.lineno(1), LSR, None)

def p_inst_lsr_iexpr(p):
    'inst : LSR iexpr'
    p[0] = INST(p.lineno(1), LSR, p[2])

def p_inst_rol(p):
    'inst : ROL'
    p[0] = INST(p.lineno(1), ROL, None)

def p_inst_rol_iexpr(p):
    'inst : ROL iexpr'
    p[0] = INST(p.lineno(1), ROL, p[2])

def p_inst_ror(p):
    'inst : ROR'
    p[0] = INST(p.lineno(1), ROR, None)

def p_inst_ror_iexpr(p):
    'inst : ROR iexpr'
    p[0] = INST(p.lineno(1), ROR, p[2])

def p_inst_jmp(p):
    'inst : JMP iexpr'
    p[0] = INST(p.lineno(1), JMP, p[2])

def p_inst_jsr(p):
    'inst : JSR NAME'
    p[0] = INST(p.lineno(1), JSR, p[2])

def p_inst_jsr_expr(p):
    'inst : JSR expr'
    p[0] = INST(p.lineno(1), JSR, p[2])

def p_inst_rts(p):
    'inst : RTS'
    p[0] = INST(p.lineno(1), RTS, None)

def p_inst_bcc(p):
    'inst : BCC NAME'
    p[0] = INST(p.lineno(1), BCC, p[2])

def p_inst_bcc_expr(p):
    'inst : BCC expr'
    p[0] = INST(p.lineno(1), BCC, p[2])

def p_inst_bcs(p):
    'inst : BCS NAME'
    p[0] = INST(p.lineno(1), BCS, p[2])

def p_inst_bcs_expr(p):
    'inst : BCS expr'
    p[0] = INST(p.lineno(1), BCS, p[2])

def p_inst_beq(p):
    'inst : BEQ NAME'
    p[0] = INST(p.lineno(1), BEQ, p[2])

def p_inst_beq_expr(p):
    'inst : BEQ expr'
    p[0] = INST(p.lineno(1), BEQ, p[2])

def p_inst_bmi(p):
    'inst : BMI NAME'
    p[0] = INST(p.lineno(1), BMI, p[2])

def p_inst_bmi_expr(p):
    'inst : BMI expr'
    p[0] = INST(p.lineno(1), BMI, p[2])

def p_inst_bne(p):
    'inst : BNE NAME'
    p[0] = INST(p.lineno(1), BNE, p[2])

def p_inst_bne_expr(p):
    'inst : BNE expr'
    p[0] = INST(p.lineno(1), BNE, p[2])

def p_inst_bpl(p):
    'inst : BPL NAME'
    p[0] = INST(p.lineno(1), BPL, p[2])

def p_inst_bpl_expr(p):
    'inst : BPL expr'
    p[0] = INST(p.lineno(1), BPL, p[2])

def p_inst_bvc(p):
    'inst : BVC NAME'
    p[0] = INST(p.lineno(1), BVC, p[2])

def p_inst_bvc_expr(p):
    'inst : BVC expr'
    p[0] = INST(p.lineno(1), BVC, p[2])

def p_inst_bvs(p):
    'inst : BVS NAME'
    p[0] = INST(p.lineno(1), BVS, p[2])

def p_inst_bvs_expr(p):
    'inst : BVS expr'
    p[0] = INST(p.lineno(1), BVS, p[2])

def p_inst_clc(p):
    'inst : CLC'
    p[0] = INST(p.lineno(1), CLC, None)

def p_inst_cld(p):
    'inst : CLD'
    p[0] = INST(p.lineno(1), CLD, None)

def p_inst_cli(p):
    'inst : CLI'
    p[0] = INST(p.lineno(1), CLI, None)

def p_inst_clv(p):
    'inst : CLV'
    p[0] = INST(p.lineno(1), CLV, None)

def p_inst_sec(p):
    'inst : SEC'
    p[0] = INST(p.lineno(1), SEC, None)

def p_inst_sed(p):
    'inst : SED'
    p[0] = INST(p.lineno(1), SED, None)

def p_inst_sei(p):
    'inst : SEI'
    p[0] = INST(p.lineno(1), SEI, None)

def p_inst_brk(p):
    'inst : BRK'
    p[0] = INST(p.lineno(1), BRK, None)

def p_inst_nop(p):
    'inst : NOP'
    p[0] = INST(p.lineno(1), NOP, None)

def p_inst_rti(p):
    'inst : RTI'
    p[0] = INST(p.lineno(1), RTI, None)

def p_const_hex(p):
    'const : HEXCONST'
    # Support both $FF and 0xFF formats
    if p[1].startswith('$'):
        p[0] = '$' + p[1][1:].upper()  # Normalize to $FF format
    else:  # 0x format
        p[0] = '$' + p[1][2:].upper()  # Convert to $FF format
    
def p_const_bin(p):
    'const : BINCONST'
    p[0] = p[1]

def p_const_dec(p):
    'const : DECCONST'
    p[0] = p[1]

def p_expr_name(p):
    'expr : NAME'
    p[0] = AstNode(AstType.AST_NAME, p[1])

def p_expr_current_addr(p):
    'expr : CURRENT_ADDR'
    p[0] = AstNode(AstType.AST_CURRENT_ADDR, "*")

def p_expr_local_label(p):
    'expr : LOCAL_LABEL'
    p[0] = AstNode(AstType.AST_LOCAL_LABEL, p[1])

def p_expr_const(p):
    'expr : const'
    p[0] = AstNode(AstType.AST_CONST, p[1])

def p_expr_immediate(p):
    'expr : "#" expr'
    p[0] = UnaryNode(AstType.AST_IMMEDIATE, p[2])

def p_expr_add(p):
    'expr : expr "+" expr'
    p[0] = BinaryNode(AstType.AST_ADD, p[1], p[3])

def p_expr_subtract(p):
    'expr : expr "-" expr'
    p[0] = BinaryNode(AstType.AST_SUBTRACT, p[1], p[3])

def p_expr_multiply(p):
    'expr : expr "*" expr'
    p[0] = BinaryNode(AstType.AST_MULTIPLY, p[1], p[3])

def p_expr_divide(p):
    'expr : expr "/" expr'
    p[0] = BinaryNode(AstType.AST_DIVIDE, p[1], p[3])

def p_expr_and(p):
    'expr : expr "&" expr'
    p[0] = BinaryNode(AstType.AST_BITWISE_AND, p[1], p[3])

def p_expr_or(p):
    'expr : expr "|" expr'
    p[0] = BinaryNode(AstType.AST_BITWISE_OR, p[1], p[3])

def p_expr_xor(p):
    'expr : expr "^" expr'
    p[0] = BinaryNode(AstType.AST_BITWISE_XOR, p[1], p[3])

def p_expr_modulo(p):
    'expr : expr "%" expr'
    p[0] = BinaryNode(AstType.AST_MODULO, p[1], p[3])

def p_expr_bitshift_left(p):
    'expr : expr "<" "<" expr'
    p[0] = BinaryNode(AstType.AST_BITSHIFT_LEFT, p[1], p[4])

def p_expr_bitshift_right(p):
    'expr : expr ">" ">" expr'
    p[0] = BinaryNode(AstType.AST_BITSHIFT_RIGHT, p[1], p[4])

def p_expr_negate(p):
    'expr : "!" expr'
    p[0] = UnaryNode(AstType.AST_NEGATE, p[2])

def p_expr_lobyte(p):
    '''expr : "<" expr
            | "." expr'''
    p[0] = UnaryNode(AstType.AST_LOBYTE, p[2])

def p_expr_hibyte(p):
    'expr : ">" expr'
    p[0] = UnaryNode(AstType.AST_HIBYTE, p[2])

def p_expr_indirect(p):
    'expr : "(" expr ")"'
    p[0] = UnaryNode(AstType.AST_INDIRECT, p[2])

def p_expr_indexed_indirect(p):
    'expr : "(" expr "," X ")"'
    # Create an indexed-x node first
    indexed = UnaryNode(AstType.AST_INDEXED_X, p[2])
    # Then wrap it in an indirect node
    p[0] = UnaryNode(AstType.AST_INDIRECT, indexed)

def p_expr_indirect_indexed(p):
    'expr : "(" expr ")" "," Y'
    # Create an indirect node first
    indirect = UnaryNode(AstType.AST_INDIRECT, p[2])
    # Then wrap it in an indexed-y node
    p[0] = UnaryNode(AstType.AST_INDEXED_Y, indirect)

def p_iexpr_expr(p):
    'iexpr : expr'
    p[0] = p[1]

def p_iexpr_indexed_x(p):
    'iexpr : expr "," X'
    p[0] = UnaryNode(AstType.AST_INDEXED_X, p[1])

def p_iexpr_indexed_y(p):
    'iexpr : expr "," Y'
    p[0] = UnaryNode(AstType.AST_INDEXED_Y, p[1])

# Error rule for syntax errors
def p_error(p):
    if p:
        print(f"Parse error at '{p.value}', line {p.lineno}")
    else:
        print("Parse error at EOF")
    sys.exit(-1)

# Build the parser
parser = yacc.yacc()

def parse(data, debug=0):
    global root
    root = RootNode()
    parser.parse(data, debug=debug)
    cleanup_ast(root)
    return root
