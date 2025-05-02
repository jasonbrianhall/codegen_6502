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

a:_var_[a-zA-Z0-9_]+ {
    /* Strip the a:_var_ prefix */
    char* varRef = strdup(yytext + 7); /* Skip past "a:_var_" */
    yylval.str = varRef;
    return NAME;
}

_var_[a-zA-Z0-9_]+ {
    /* Strip the _var_ prefix */
    char* varName = strdup(yytext + 5); /* Skip past "_var_" */
    yylval.str = varName;
    return NAME;
}

_label_[a-zA-Z0-9_]+: {
    /* Strip the _label_ prefix and the trailing colon */
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  /* Remove colon */
    char* labelName = originalText + 7;  /* Skip past "_label_" */
    yylval.str = strdup(labelName);
    free(originalText);  /* Free the temporary string */
    return LABEL;
}

_label_[a-zA-Z0-9_]+ {
    /* Strip the _label_ prefix for label references (no colon) */
    char* labelRef = strdup(yytext + 7); /* Skip past "_label_" */
    yylval.str = labelRef;
    return NAME;
}

_func_[a-zA-Z0-9_]+ {
    /* Strip the _func_ prefix for function references */
    char* funcRef = strdup(yytext + 6); /* Skip past "_func_" */
    yylval.str = funcRef;
    return NAME;
}

_func_[a-zA-Z0-9_]+: {
    /* Strip the _func_ prefix and the trailing colon */
    char* originalText = strdup(yytext);
    int len = strlen(originalText);
    originalText[len-1] = '\0';  /* Remove colon */
    char* funcName = originalText + 6;  /* Skip past "_func_" */
    yylval.str = strdup(funcName);
    free(originalText);  /* Free the temporary string */
    return LABEL;
}

_jump_[a-zA-Z0-9_]+ {
    /* Strip the _jump_ prefix */
    char* jumpRef = strdup(yytext + 6); /* Skip past "_jump_" */
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
