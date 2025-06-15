/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_JBHALL_SOFTWARE_BUILD_CODEGEN_6502_CODEGEN_PARSER_HPP_INCLUDED
# define YY_YY_HOME_JBHALL_SOFTWARE_BUILD_CODEGEN_6502_CODEGEN_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DIRECTIVE = 258,               /* DIRECTIVE  */
    NAME = 259,                    /* NAME  */
    LABEL = 260,                   /* LABEL  */
    DATABYTES = 261,               /* DATABYTES  */
    DATAWORDS = 262,               /* DATAWORDS  */
    HEXCONST = 263,                /* HEXCONST  */
    BINCONST = 264,                /* BINCONST  */
    DECCONST = 265,                /* DECCONST  */
    STRINGCONST = 266,             /* STRINGCONST  */
    LDA = 267,                     /* LDA  */
    LDX = 268,                     /* LDX  */
    LDY = 269,                     /* LDY  */
    STA = 270,                     /* STA  */
    STX = 271,                     /* STX  */
    STY = 272,                     /* STY  */
    TAX = 273,                     /* TAX  */
    TAY = 274,                     /* TAY  */
    TXA = 275,                     /* TXA  */
    TYA = 276,                     /* TYA  */
    TSX = 277,                     /* TSX  */
    TXS = 278,                     /* TXS  */
    PHA = 279,                     /* PHA  */
    PHP = 280,                     /* PHP  */
    PLA = 281,                     /* PLA  */
    PLP = 282,                     /* PLP  */
    AND = 283,                     /* AND  */
    EOR = 284,                     /* EOR  */
    ORA = 285,                     /* ORA  */
    BIT = 286,                     /* BIT  */
    ADC = 287,                     /* ADC  */
    SBC = 288,                     /* SBC  */
    CMP = 289,                     /* CMP  */
    CPX = 290,                     /* CPX  */
    CPY = 291,                     /* CPY  */
    INC = 292,                     /* INC  */
    INX = 293,                     /* INX  */
    INY = 294,                     /* INY  */
    DEC = 295,                     /* DEC  */
    DEX = 296,                     /* DEX  */
    DEY = 297,                     /* DEY  */
    ASL = 298,                     /* ASL  */
    LSR = 299,                     /* LSR  */
    ROL = 300,                     /* ROL  */
    ROR = 301,                     /* ROR  */
    JMP = 302,                     /* JMP  */
    JSR = 303,                     /* JSR  */
    RTS = 304,                     /* RTS  */
    BCC = 305,                     /* BCC  */
    BCS = 306,                     /* BCS  */
    BEQ = 307,                     /* BEQ  */
    BMI = 308,                     /* BMI  */
    BNE = 309,                     /* BNE  */
    BPL = 310,                     /* BPL  */
    BVC = 311,                     /* BVC  */
    BVS = 312,                     /* BVS  */
    CLC = 313,                     /* CLC  */
    CLD = 314,                     /* CLD  */
    CLI = 315,                     /* CLI  */
    CLV = 316,                     /* CLV  */
    SEC = 317,                     /* SEC  */
    SED = 318,                     /* SED  */
    SEI = 319,                     /* SEI  */
    BRK = 320,                     /* BRK  */
    NOP = 321,                     /* NOP  */
    RTI = 322,                     /* RTI  */
    SLO = 323,                     /* SLO  */
    DATASPACE = 324,               /* DATASPACE  */
    BASEADDR = 325                 /* BASEADDR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 36 "asm6502.y"

    const char* str;
    AstNode* node;
    ListNode* list;
    InstructionNode* instruction;

#line 141 "/home/jbhall/software_build/codegen_6502/codegen/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_HOME_JBHALL_SOFTWARE_BUILD_CODEGEN_6502_CODEGEN_PARSER_HPP_INCLUDED  */
