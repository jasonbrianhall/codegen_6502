// Add these functions to util.hpp
#ifndef AST_DEBUG_UTILS_HPP
#define AST_DEBUG_UTILS_HPP

#include <iostream>
#include <string>
#include "ast.hpp"

// Convert AST node type to string for debugging
const char* getAstTypeString(AstType type) {
    switch (type) {
        case AST_ROOT: return "AST_ROOT";
        case AST_LIST: return "AST_LIST";
        case AST_DATA8: return "AST_DATA8";
        case AST_DATA16: return "AST_DATA16";
        case AST_DECL: return "AST_DECL";
        case AST_LABEL: return "AST_LABEL";
        case AST_NAME: return "AST_NAME";
        case AST_CONST: return "AST_CONST";
        case AST_IMMEDIATE: return "AST_IMMEDIATE";
        case AST_INDIRECT: return "AST_INDIRECT";
        case AST_INDEXED_X: return "AST_INDEXED_X";
        case AST_INDEXED_Y: return "AST_INDEXED_Y";
        case AST_LOBYTE: return "AST_LOBYTE";
        case AST_HIBYTE: return "AST_HIBYTE";
        case AST_ADD: return "AST_ADD";
        case AST_SUBTRACT: return "AST_SUBTRACT";
        case AST_INSTRUCTION: return "AST_INSTRUCTION";
        default: return "UNKNOWN_TYPE";
    }
}

// Print details about an AST node for debugging
void printNodeDetails(AstNode* node, int indent = 0) {
    if (!node) {
        for (int i = 0; i < indent; i++) std::cout << "  ";
        std::cout << "NULL node" << std::endl;
        return;
    }
    
    for (int i = 0; i < indent; i++) std::cout << "  ";
    
    std::cout << "Node Type: " << getAstTypeString(node->type) 
              << " (Line: " << node->lineNumber << ")" << std::endl;
    
    // Print more details based on node type
    switch (node->type) {
        case AST_LABEL: {
            LabelNode* label = static_cast<LabelNode*>(node);
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Label: " << (label->value.s ? label->value.s : "NULL")
                      << ", Type: " << label->labelType << std::endl;
            
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Child: " << std::endl;
            printNodeDetails(label->child, indent + 2);
            break;
        }
        case AST_LIST: {
            ListNode* list = static_cast<ListNode*>(node);
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Value: " << std::endl;
            printNodeDetails(list->value.node, indent + 2);
            
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Next: " << std::endl;
            printNodeDetails(list->next, indent + 2);
            break;
        }
        case AST_NAME:
        case AST_CONST: {
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Value: " << (node->value.s ? node->value.s : "NULL") << std::endl;
            break;
        }
        case AST_INSTRUCTION: {
            InstructionNode* inst = static_cast<InstructionNode*>(node);
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Code: " << inst->code << std::endl;
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "  Operand: " << std::endl;
            printNodeDetails(inst->value.node, indent + 2);
            break;
        }
        default:
            // For other types, just show the basic info already printed
            break;
    }
}

// Print the entire AST for debugging
void dumpAst(RootNode* root) {
    std::cout << "=== AST Dump ===" << std::endl;
    std::cout << "Root has " << root->children.size() << " children" << std::endl;
    
    int index = 0;
    for (std::list<AstNode*>::iterator it = root->children.begin();
         it != root->children.end(); ++it, ++index) {
        std::cout << "Child " << index << ":" << std::endl;
        printNodeDetails(*it, 1);
        std::cout << "---" << std::endl;
    }
    
    std::cout << "=== End AST Dump ===" << std::endl;
}

#endif // AST_DEBUG_UTILS_HPP
