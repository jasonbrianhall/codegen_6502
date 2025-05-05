#!/usr/bin/env python3
"""
Python implementation of the AST classes
Converted from original ast.hpp/ast.cpp files
"""

import sys
from enum import Enum, auto

# Token/AST type definitions
# Enums for AST node types
class AstType(Enum):
    AST_ROOT = auto()
    AST_LIST = auto()
    AST_DATA8 = auto()
    AST_DATA16 = auto()
    AST_DECL = auto()
    AST_LABEL = auto()
    AST_NAME = auto()
    AST_CONST = auto()
    AST_IMMEDIATE = auto()
    AST_INDIRECT = auto()
    AST_INDEXED_X = auto()
    AST_INDEXED_Y = auto()
    AST_LOBYTE = auto()
    AST_HIBYTE = auto()
    AST_ADD = auto()
    AST_SUBTRACT = auto()
    AST_INSTRUCTION = auto()

# 6502 Instruction opcodes - using the same numeric values as in the original code
# These would normally be defined in parser.hpp
# In the Python version, we're defining them here for simplicity
LDA = 1
LDX = 2
LDY = 3
STA = 4
STX = 5
STY = 6
TAX = 7
TAY = 8
TXA = 9
TYA = 10
TSX = 11
TXS = 12
PHA = 13
PHP = 14
PLA = 15
PLP = 16
AND = 17
EOR = 18
ORA = 19
BIT = 20
ADC = 21
SBC = 22
CMP = 23
CPX = 24
CPY = 25
INC = 26
INX = 27
INY = 28
DEC = 29
DEX = 30
DEY = 31
ASL = 32
LSR = 33
ROL = 34
ROR = 35
JMP = 36
JSR = 37
RTS = 38
BCC = 39
BCS = 40
BEQ = 41
BMI = 42
BNE = 43
BPL = 44
BVC = 45
BVS = 46
CLC = 47
CLD = 48
CLI = 49
CLV = 50
SEC = 51
SED = 52
SEI = 53
BRK = 54
NOP = 55
RTI = 56
SLO = 57

# AstValue union - in Python we'll use a simple class
class AstValue:
    def __init__(self):
        self.s = None
        self.node = None
        self.ptr = None

# Base AST node class
class AstNode:
    def __init__(self, node_type, value=None):
        self.type = node_type
        self.value = AstValue()
        if value is not None:
            self.value.s = value
        self.parent = None
        self.line_number = 0
        
# Unary node (node with one child)
class UnaryNode(AstNode):
    def __init__(self, node_type, child):
        super().__init__(node_type)
        self.child = child

# Binary node (node with two children)
class BinaryNode(AstNode):
    def __init__(self, node_type, lhs, rhs):
        super().__init__(node_type)
        self.lhs = lhs
        self.rhs = rhs

# Root node for the AST
class RootNode(AstNode):
    def __init__(self):
        super().__init__(AstType.AST_ROOT)
        self.children = []

# List node for sequences
class ListNode(AstNode):
    def __init__(self):
        super().__init__(AstType.AST_LIST)
        self.next = None

# Declaration node
class DeclNode(AstNode):
    def __init__(self, name, expression):
        super().__init__(AstType.AST_DECL)
        self.value.s = name
        self.expression = expression

# Label types enum
class LabelType(Enum):
    LABEL_NONE = auto()  # Undefined label
    LABEL_ALIAS = auto() # Alias for another label
    LABEL_CODE = auto()  # Label containing strictly code
    LABEL_DATA = auto()  # Label containing strictly data

# Label node
class LabelNode(AstNode):
    def __init__(self, name, child):
        super().__init__(AstType.AST_LABEL)
        self.label_type = LabelType.LABEL_NONE
        self.value.s = name
        self.child = child

# Instruction node
class InstructionNode(AstNode):
    def __init__(self, code, operand=None):
        super().__init__(AstType.AST_INSTRUCTION)
        self.code = code
        if operand is not None:
            self.value.ptr = operand
            # In the Python implementation, we'll directly store the node for simplicity
            # This makes the code cleaner compared to the C++ void* approach
            self.value.node = operand

# Function to reverse a linked list (from the C++ cleanupNode)
def reverse_list(prev, node):
    """
    Recursively reverses a linked list
    """
    if node.next is None:
        # We're at the end
        node.next = prev
        return node
    else:
        next_node = node.next
        # Switch directions of the pointers
        node.next = prev
        return reverse_list(node, next_node)

# Recursive cleanup function for list nodes
def cleanup_list(node):
    """
    Recursively clean up a list node
    """
    if node is not None:
        cleanup_node(node.value.node)
        cleanup_list(node.next)

# Cleanup a node in the AST
def cleanup_node(node):
    """
    Clean up an AST node (similar to C++ cleanupNode function)
    """
    if node is not None:
        if node.type == AstType.AST_LIST:
            n = node
            node = reverse_list(None, n)
            cleanup_list(node)
        elif node.type == AstType.AST_DATA8 or node.type == AstType.AST_DATA16:
            cleanup_node(node.value.node)
        elif node.type == AstType.AST_DECL:
            d = node
            cleanup_node(d.expression)
        elif node.type == AstType.AST_LABEL:
            n = node
            cleanup_node(n.child)

# Cleanup the entire AST
def cleanup_ast(root):
    """
    Clean up the entire AST (similar to C++ cleanupAst function)
    """
    for node in root.children:
        cleanup_node(node)

# Print indentation for AST visualization
def print_indent(indent):
    """
    Print indentation for AST visualization
    """
    print(" " * indent, end="")

# Print a node in the AST (for debugging)
def print_node(node, indent=0):
    """
    Print a node in the AST (similar to C++ printNode function)
    """
    if node is None:
        return
        
    if node.type == AstType.AST_LIST:
        n = node
        print_indent(indent)
        print("list element:")
        print_node(n.value.node, indent + 4)
        print_node(n.next, indent)
    elif node.type == AstType.AST_DATA8:
        print_indent(indent)
        print("data:")
        print_node(node.value.node, indent + 4)
    elif node.type == AstType.AST_DATA16:
        print_indent(indent)
        print("data (16 bit):")
        print_node(node.value.node, indent + 4)
    elif node.type == AstType.AST_DECL:
        d = node
        print_indent(indent)
        print(f"decl: {d.value.s} = ")
        print_node(d.expression, indent + 4)
    elif node.type == AstType.AST_LABEL:
        n = node
        print_indent(indent)
        print(f"label: {n.value.s}")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_NAME:
        print_indent(indent)
        print(f"name: {node.value.s}")
    elif node.type == AstType.AST_CONST:
        print_indent(indent)
        print(f"constant: {node.value.s}")
    elif node.type == AstType.AST_IMMEDIATE:
        n = node
        print_indent(indent)
        print("immediate:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_INDIRECT:
        n = node
        print_indent(indent)
        print("indirect:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_INDEXED_X:
        n = node
        print_indent(indent)
        print("indexed x:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_INDEXED_Y:
        n = node
        print_indent(indent)
        print("indexed y:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_LOBYTE:
        n = node
        print_indent(indent)
        print("low byte:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_HIBYTE:
        n = node
        print_indent(indent)
        print("high byte:")
        print_node(n.child, indent + 4)
    elif node.type == AstType.AST_ADD:
        n = node
        print_indent(indent)
        print("add:")
        print_node(n.lhs, indent + 4)
        print_node(n.rhs, indent + 4)
    elif node.type == AstType.AST_SUBTRACT:
        n = node
        print_indent(indent)
        print("subtract:")
        print_node(n.lhs, indent + 4)
        print_node(n.rhs, indent + 4)
    elif node.type == AstType.AST_INSTRUCTION:
        n = node
        print_indent(indent)
        print(f"instruction (line {n.line_number}) {n.code}:")
        print_node(n.value.node, indent + 4)
