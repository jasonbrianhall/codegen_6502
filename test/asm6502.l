%option noyywrap
%option yylineno

%{
#include <string.h>
#include "ast.hpp"
#include "util.hpp"
#include "parser.hpp"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

void yyerror(const char *);
%}

%%
[ \t\r\n]+ {
    ;
}

;.* {
    mapComment(yylineno, yytext);
}

\.db {
    return DATABYTES;
}

\.byte {
    return DATABYTES; // Map .byte to the same token as .db
}

\.dw {
    return DATAWORDS;
}

\"[^\"]*\" {
    yylval.str = DUP_YYTEXT;
    return STRING;
}

\.[a-z]+ {
    yylval.str = DUP_YYTEXT;
    return DIRECTIVE;
}

\(_var_[a-zA-Z0-9_]+,X\) {
    // Extract variable name without parentheses and register
    char* originalText = strdup(yytext + 1); // Skip the opening parenthesis
    char* commaPos = strchr(originalText, ',');
    *commaPos = '\0';  // Terminate at the comma
    
    // Skip past "_var_"
    char* varName = originalText + 5;
    
    char* result = strdup(varName);
    free(originalText);
    
    // Create a node with the indirect-indexed addressing mode
    yylval.str = result;
    return NAME;
}

\(_var_[a-zA-Z0-9_]+,Y\) {
    // Extract variable name without parentheses and register
    char* originalText = strdup(yytext + 1); // Skip the opening parenthesis
    char* commaPos = strchr(originalText, ',');
    *commaPos = '\0';  // Terminate at the comma
    
    // Skip past "_var_"
    char* varName = originalText + 5;
    
    char* result = strdup(varName);
    free(originalText);
    
    // Create a node with the indirect-indexed addressing mode
    yylval.str = result;
    return NAME;
}

a:\$[0-9A-Fa-f]+ {
    // Strip the "a:" prefix and keep the hex constant
    char* hexRef = strdup(yytext + 2); // Skip past "a:"
    yylval.str = hexRef;
    return HEXCONST;
}

z:\$[0-9A-Fa-f]+ {
    // Strip the "z:" prefix and keep the hex constant
    char* hexRef = strdup(yytext + 2); // Skip past "z:"
    yylval.str = hexRef;
    return HEXCONST;
}

z:_var_[a-zA-Z0-9_]+ {
    // Strip the z:_var_ prefix
    char* varRef = strdup(yytext + 7); // Skip past "z:_var_"
    yylval.str = varRef;
    return NAME;
}

_data_[a-zA-Z0-9_]+: {
    // Strip the _data_ prefix and the trailing colon
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  // Remove colon
    char* dataName = originalText + 6;  // Skip past "_data_"
    yylval.str = strdup(dataName);
    free(originalText);  // Free the temporary string
    return LABEL;
}

_jump_[a-zA-Z0-9_]+: {
    // Strip the _jump_ prefix and the trailing colon
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  // Remove colon
    char* jumpName = originalText + 6;  // Skip past "_jump_"
    yylval.str = strdup(jumpName);
    free(originalText);  // Free the temporary string
    return LABEL;
}

a:[a-zA-Z][a-zA-Z0-9_]* {
    // Strip the "a:" prefix and keep the name
    char* nameRef = strdup(yytext + 2); // Skip past "a:"
    yylval.str = nameRef;
    return NAME;
}

a:_data_[a-zA-Z0-9_]+,X {
    // Extract just the data name (without prefix and indexing)
    char* originalText = strdup(yytext);
    char* commaPos = strchr(originalText, ',');
    *commaPos = '\0';  // Terminate string at the comma
    
    // Skip past "a:_data_"
    char* dataName = originalText + 8;
    
    char* result = strdup(dataName);
    free(originalText);
    
    yylval.str = result;
    return NAME;
}

a:_data_[a-zA-Z0-9_]+,Y {
    // Extract just the data name (without prefix and indexing)
    char* originalText = strdup(yytext);
    char* commaPos = strchr(originalText, ',');
    *commaPos = '\0';  // Terminate string at the comma
    
    // Skip past "a:_data_"
    char* dataName = originalText + 8;
    
    char* result = strdup(dataName);
    free(originalText);
    
    yylval.str = result;
    return NAME;
}

a:_data_[a-zA-Z0-9_]+ {
    // Skip past "a:_data_"
    char* dataName = strdup(yytext + 8);
    yylval.str = dataName;
    return NAME;
}

a:_var_[a-zA-Z0-9_]+ {
    // Strip the a:_var_ prefix
    char* varRef = strdup(yytext + 7); // Skip past "a:_var_"
    yylval.str = varRef;
    return NAME;
}

_var_[a-zA-Z0-9_]+ {
    // Strip the _var_ prefix
    char* varName = strdup(yytext + 5); // Skip past "_var_"
    yylval.str = varName;
    return NAME;
}

_label_[a-zA-Z0-9_]+: {
    // Strip the _label_ prefix and the trailing colon
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  // Remove colon
    char* labelName = originalText + 7;  // Skip past "_label_"
    yylval.str = strdup(labelName);
    free(originalText);  // Free the temporary string
    return LABEL;
}

_label_[a-zA-Z0-9_]+ {
    // Strip the _label_ prefix for label references (no colon)
    char* labelRef = strdup(yytext + 7); // Skip past "_label_"
    yylval.str = labelRef;
    return NAME;
}

_func_[a-zA-Z0-9_]+ {
    // Strip the _func_ prefix for function references
    char* funcRef = strdup(yytext + 6); // Skip past "_func_"
    yylval.str = funcRef;
    return NAME;
}

_func_[a-zA-Z0-9_]+: {
    // Strip the _func_ prefix and the trailing colon
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  // Remove colon
    char* funcName = originalText + 6;  // Skip past "_func_"
    yylval.str = strdup(funcName);
    free(originalText);  // Free the temporary string
    return LABEL;
}

_jump_[a-zA-Z0-9_]+ {
    // Strip the _jump_ prefix
    char* jumpRef = strdup(yytext + 6); // Skip past "_jump_"
    yylval.str = jumpRef;
    return NAME;
}

[a-zA-Z]+[a-zA-Z0-9_]*: {
    yylval.str = DUP_YYTEXT;
    return LABEL;
}

[xX] {
    return 'x'; // Always return lowercase for consistency
}

[yY] {
    return 'y'; // Always return lowercase for consistency
}

lda {
    return LDA;
}

ldx {
    return LDX;
}

ldy {
    return LDY;
}

sta {
    return STA;
}

stx {
    return STX;
}

sty {
    return STY;
}

tax {
    return TAX;
}

tay {
    return TAY;
}

txa {
    return TXA;
}

tya {
    return TYA;
}

tsx {
    return TSX;
}

txs {
    return TXS;
}

pha {
    return PHA;
}

php {
    return PHP;
}

pla {
    return PLA;
}

plp {
    return PLP;
}

and {
    return AND;
}

eor {
    return EOR;
}

ora {
    return ORA;
}

bit {
    return BIT;
}

adc {
    return ADC;
}

sbc {
    return SBC;
}

cmp {
    return CMP;
}

cpx {
    return CPX;
}

cpy {
    return CPY;
}

inc {
    return INC;
}

inx {
    return INX;
}

iny {
    return INY;
}

dec {
    return DEC;
}

dex {
    return DEX;
}

dey {
    return DEY;
}

asl {
    return ASL;
}

lsr {
    return LSR;
}

rol {
    return ROL;
}

ror {
    return ROR;
}

jmp {
    return JMP;
}

jsr {
    return JSR;
}

rts {
    return RTS;
}

bcc {
    return BCC;
}

bcs {
    return BCS;
}

beq {
    return BEQ;
}

bmi {
    return BMI;
}

bne {
    return BNE;
}

bpl {
    return BPL;
}

bvc {
    return BVC;
}

bvs {
    return BVS;
}

clc {
    return CLC;
}

cld {
    return CLD;
}

cli {
    return CLI;
}

clv {
    return CLV;
}

sec {
    return SEC;
}

sed {
    return SED;
}

sei {
    return SEI;
}

brk {
    return BRK;
}

nop {
    return NOP;
}

rti {
    return RTI;
}

sax {
    // Custom instruction, handle it like STA
    return STA;
}

[a-zA-Z]+[a-zA-Z0-9_]* {
    yylval.str = DUP_YYTEXT;
    return NAME;
}

\$[0-9A-Fa-f]+ {
    yylval.str = DUP_YYTEXT;
    return HEXCONST;
}

%[0|1]+ {
    yylval.str = DUP_YYTEXT;
    return BINCONST;
}

[0-9]+ {
    yylval.str = DUP_YYTEXT;
    return DECCONST;
}

= {
    return *yytext;
}

\+ {
    return *yytext;
}

\- {
    return *yytext;
}

\< {
    return *yytext;
}

\> {
    return *yytext;
}

# {
    return *yytext;
}

, {
    return *yytext;
}

\( {
    return *yytext;
}

\) {
    return *yytext;
}

. {
    printf("invalid token (line %d): %s\n", yylineno, yytext);
    yyerror(yytext);
}

%%
