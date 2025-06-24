"""
AST Node Classes for 6502 Assembly Code Generator - FIXED VERSION WITH DEBUGGING
"""

from enum import Enum
from typing import List, Optional, Union, Any
import re

class AstType(Enum):
    AST_ROOT = "root"
    AST_LIST = "list"
    AST_DATA8 = "data8"
    AST_DATA16 = "data16"
    AST_DECL = "decl"
    AST_LABEL = "label"
    AST_NAME = "name"
    AST_CONST = "const"
    AST_IMMEDIATE = "immediate"
    AST_INDIRECT = "indirect"
    AST_INDEXED_X = "indexed_x"
    AST_INDEXED_Y = "indexed_y"
    AST_LOBYTE = "lobyte"
    AST_HIBYTE = "hibyte"
    AST_ADD = "add"
    AST_SUBTRACT = "subtract"
    AST_INSTRUCTION = "instruction"

class LabelType(Enum):
    LABEL_NONE = "none"
    LABEL_ALIAS = "alias"
    LABEL_CODE = "code"
    LABEL_DATA = "data"

class AstNode:
    def __init__(self, ast_type: AstType, value: Any = None):
        self.type = ast_type
        self.value = value
        self.parent: Optional['AstNode'] = None
        self.line_number = 0

class UnaryNode(AstNode):
    def __init__(self, ast_type: AstType, child: AstNode):
        super().__init__(ast_type)
        self.child = child

class BinaryNode(AstNode):
    def __init__(self, ast_type: AstType, lhs: AstNode, rhs: AstNode):
        super().__init__(ast_type)
        self.lhs = lhs
        self.rhs = rhs

class RootNode(AstNode):
    def __init__(self):
        super().__init__(AstType.AST_ROOT)
        self.children: List[AstNode] = []

class ListNode(AstNode):
    def __init__(self):
        super().__init__(AstType.AST_LIST)
        self.next: Optional['ListNode'] = None

class DeclNode(AstNode):
    def __init__(self, name: str, expression: AstNode):
        super().__init__(AstType.AST_DECL)
        self.value = name
        self.expression = expression

class LabelNode(AstNode):
    def __init__(self, name: str, child: AstNode):
        super().__init__(AstType.AST_LABEL)
        self.label_type = LabelType.LABEL_NONE
        self.value = name
        self.child = child

class InstructionNode(AstNode):
    def __init__(self, code: int, operand: Any = None):
        super().__init__(AstType.AST_INSTRUCTION)
        self.code = code
        self.value = operand

def cleanup_ast(root: RootNode, debug: bool = False):
    """Enhanced AST cleanup with debugging - PRESERVES source code order"""
    if debug:
        print(f"\n=== AST CLEANUP DEBUG ===")
        print(f"Root has {len(root.children)} children before cleanup")
        
        # Show what we have before cleanup
        for i, node in enumerate(root.children):
            if node.type == AstType.AST_LABEL:
                print(f"  [{i}] LABEL: {node.value} (line {node.line_number})")
            elif node.type == AstType.AST_DECL:
                print(f"  [{i}] DECL: {node.value}")
            else:
                print(f"  [{i}] {node.type.name}")
    
    # Clean up each child node but MAINTAIN ORDER
    for i, node in enumerate(root.children):
        root.children[i] = cleanup_node(node, debug)
    
    if debug:
        print(f"Root has {len(root.children)} children after cleanup")
        print("=== END AST CLEANUP DEBUG ===\n")

def cleanup_node(node: AstNode, debug: bool = False):
    """Enhanced cleanup of individual AST nodes - PRESERVES ORDER"""
    if node is None:
        return node
    
    if debug and node.type == AstType.AST_LABEL:
        print(f"    Cleaning up label: {node.value}")
    
    if node.type == AstType.AST_LIST:
        # CRITICAL: Do NOT reverse the list - keep source code order
        cleanup_list(node, debug)
        return node
    elif node.type in [AstType.AST_DATA8, AstType.AST_DATA16]:
        if hasattr(node, 'value') and node.value:
            node.value = cleanup_node(node.value, debug)
    elif node.type == AstType.AST_DECL:
        if hasattr(node, 'expression') and node.expression:
            node.expression = cleanup_node(node.expression, debug)
    elif node.type == AstType.AST_LABEL:
        if hasattr(node, 'child') and node.child:
            node.child = cleanup_node(node.child, debug)
    
    return node

def cleanup_list(node: Optional[ListNode], debug: bool = False):
    """Enhanced cleanup of list nodes - PRESERVES ORDER"""
    item_count = 0
    current = node
    
    while current is not None:
        if hasattr(current, 'value') and current.value:
            current.value = cleanup_node(current.value, debug)
        item_count += 1
        current = current.next
    
    if debug and item_count > 0:
        print(f"      Cleaned list with {item_count} items")

def validate_ast_integrity(root: RootNode, source_lines: List[str] = None):
    """Validate AST integrity and detect missing sections"""
    print(f"\n=== AST INTEGRITY VALIDATION ===")
    
    labels_found = []
    total_instructions = 0
    total_data = 0
    
    for child in root.children:
        if child.type == AstType.AST_LABEL:
            labels_found.append((child.value, child.line_number))
            
            # Count instructions and data in this label
            inst_count, data_count = count_label_content(child.child)
            total_instructions += inst_count
            total_data += data_count
            
            print(f"  LABEL: {child.value} (line {child.line_number}) - {inst_count} instructions, {data_count} data")
        elif child.type == AstType.AST_DECL:
            print(f"  DECL: {child.value}")
    
    print(f"\nSummary:")
    print(f"  {len(labels_found)} labels found")
    print(f"  {total_instructions} total instructions")
    print(f"  {total_data} total data items")
    
    # Check for sequential gaps if source lines provided
    if source_lines:
        check_for_missing_labels(labels_found, source_lines)
    
    print("=== END VALIDATION ===\n")

def count_label_content(list_node: Optional[ListNode]) -> tuple:
    """Count instructions and data items in a label's content"""
    inst_count = 0
    data_count = 0
    
    current = list_node
    while current is not None:
        if hasattr(current, 'value') and current.value:
            if current.value.type == AstType.AST_INSTRUCTION:
                inst_count += 1
            elif current.value.type in [AstType.AST_DATA8, AstType.AST_DATA16]:
                data_count += 1
        current = current.next
    
    return inst_count, data_count

def check_for_missing_labels(parsed_labels: List[tuple], source_lines: List[str]):
    """Check for labels that might be missing from the AST"""
    
    # Extract all labels from source
    source_labels = []
    for line_num, line in enumerate(source_lines, 1):
        match = re.match(r'^([a-zA-Z_][a-zA-Z0-9_]*):', line.strip())
        if match:
            label_name = match.group(1) + ":"
            source_labels.append((label_name, line_num))
    
    print(f"\nLabel comparison:")
    print(f"  Source has {len(source_labels)} labels")
    print(f"  Parsed {len(parsed_labels)} labels")
    
    # Find missing labels
    parsed_names = set(label[0] for label in parsed_labels)
    missing_labels = []
    
    for source_label, line_num in source_labels:
        if source_label not in parsed_names:
            missing_labels.append((source_label, line_num))
    
    if missing_labels:
        print(f"\n  WARNING: {len(missing_labels)} labels appear to be missing:")
        for label, line_num in missing_labels[:10]:  # Show first 10
            print(f"    {label} (line {line_num})")
        if len(missing_labels) > 10:
            print(f"    ... and {len(missing_labels) - 10} more")
    else:
        print(f"  ✓ All source labels found in AST")

def print_node(node: AstNode, indent: int = 0):
    """Enhanced print function for debugging AST structure"""
    if node is None:
        return
    
    indent_str = " " * indent
    
    if node.type == AstType.AST_LIST:
        print(f"{indent_str}list element:")
        if hasattr(node, 'value') and node.value:
            print_node(node.value, indent + 4)
        if hasattr(node, 'next') and node.next:
            print_node(node.next, indent)
    elif node.type == AstType.AST_DATA8:
        print(f"{indent_str}data (.db):")
        if hasattr(node, 'value') and node.value:
            print_node(node.value, indent + 4)
    elif node.type == AstType.AST_DATA16:
        print(f"{indent_str}data (.dw):")
        if hasattr(node, 'value') and node.value:
            print_node(node.value, indent + 4)
    elif node.type == AstType.AST_DECL:
        print(f"{indent_str}decl: {node.value} =")
        if hasattr(node, 'expression') and node.expression:
            print_node(node.expression, indent + 4)
    elif node.type == AstType.AST_LABEL:
        content_summary = ""
        if hasattr(node, 'child') and node.child:
            inst_count, data_count = count_label_content(node.child)
            content_summary = f" ({inst_count} inst, {data_count} data)"
        print(f"{indent_str}label: {node.value} (line {node.line_number}){content_summary}")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_NAME:
        print(f"{indent_str}name: {node.value}")
    elif node.type == AstType.AST_CONST:
        print(f"{indent_str}constant: {node.value}")
    elif node.type == AstType.AST_IMMEDIATE:
        print(f"{indent_str}immediate:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_INDIRECT:
        print(f"{indent_str}indirect:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_INDEXED_X:
        print(f"{indent_str}indexed x:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_INDEXED_Y:
        print(f"{indent_str}indexed y:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_LOBYTE:
        print(f"{indent_str}low byte:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_HIBYTE:
        print(f"{indent_str}high byte:")
        if hasattr(node, 'child') and node.child:
            print_node(node.child, indent + 4)
    elif node.type == AstType.AST_ADD:
        print(f"{indent_str}add:")
        if hasattr(node, 'lhs') and node.lhs:
            print_node(node.lhs, indent + 4)
        if hasattr(node, 'rhs') and node.rhs:
            print_node(node.rhs, indent + 4)
    elif node.type == AstType.AST_SUBTRACT:
        print(f"{indent_str}subtract:")
        if hasattr(node, 'lhs') and node.lhs:
            print_node(node.lhs, indent + 4)
        if hasattr(node, 'rhs') and node.rhs:
            print_node(node.rhs, indent + 4)
    elif node.type == AstType.AST_INSTRUCTION:
        print(f"{indent_str}instruction (line {node.line_number}) code={node.code}:")
        if hasattr(node, 'value') and node.value:
            print_node(node.value, indent + 4)
