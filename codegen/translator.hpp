#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <list>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <set>
#include <algorithm>


#include "ast.hpp"

class Translator
{
public:
    Translator(const std::string& inputFilename, RootNode* astRootNode);

    std::string getConstantHeaderOutput() const;
    std::string getDataOutput() const;
    std::string getDataHeaderOutput() const;
    std::string getSourceOutput() const;

private:
    std::set<std::string> referencedDataLabels;  // Track all referenced data labels
    
    void trackDataReference(const std::string& name);
    void generateMissingDataDeclarations();

    std::string inputFilename;
    std::stringstream constantHeaderOutput;
    std::stringstream dataOutput;
    std::stringstream dataHeaderOutput;
    std::stringstream sourceOutput;
    RootNode* root;
    int returnLabelIndex;
    void classifyLabels();
    void generateCode();
    void generateConstantDeclarations();
    void generateDataDeclarations();
    void indexEmptyLines();
    void translate();
    std::string translateBranch(const std::string& condition, const std::string& destination);
    std::string translateExpression(AstNode* expr);
    std::string translateInstruction(InstructionNode* inst);
    std::string translateOperand(AstNode* operand);

    std::map<std::string, uint16_t> labelAddresses;  // Map label names to their addresses
    bool hasIndirectJumps;  // Track if we need to generate the dispatcher
    void calculateLabelAddresses();
    void generateIndirectJumpDispatcher();

};

#endif // TRANSLATOR_HPP
