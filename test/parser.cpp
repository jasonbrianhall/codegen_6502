/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "asm6502.y"

#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "ast.hpp"
#include "translator.hpp"

extern int yylex();
extern FILE* yyin;
extern int yylineno;

RootNode* root = NULL;

void yyerror(const char* s);

// Short hand for an instruction AST node
// there are so many of them, so this saves some typing
//
#define INST(t, r, c, o) \
    r = new InstructionNode(c, o); r->lineNumber = t.first_line;

#line 94 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_DIRECTIVE = 4,                  /* DIRECTIVE  */
  YYSYMBOL_NAME = 5,                       /* NAME  */
  YYSYMBOL_LABEL = 6,                      /* LABEL  */
  YYSYMBOL_DATABYTES = 7,                  /* DATABYTES  */
  YYSYMBOL_DATAWORDS = 8,                  /* DATAWORDS  */
  YYSYMBOL_HEXCONST = 9,                   /* HEXCONST  */
  YYSYMBOL_BINCONST = 10,                  /* BINCONST  */
  YYSYMBOL_DECCONST = 11,                  /* DECCONST  */
  YYSYMBOL_LDA = 12,                       /* LDA  */
  YYSYMBOL_LDX = 13,                       /* LDX  */
  YYSYMBOL_LDY = 14,                       /* LDY  */
  YYSYMBOL_STA = 15,                       /* STA  */
  YYSYMBOL_STX = 16,                       /* STX  */
  YYSYMBOL_STY = 17,                       /* STY  */
  YYSYMBOL_TAX = 18,                       /* TAX  */
  YYSYMBOL_TAY = 19,                       /* TAY  */
  YYSYMBOL_TXA = 20,                       /* TXA  */
  YYSYMBOL_TYA = 21,                       /* TYA  */
  YYSYMBOL_TSX = 22,                       /* TSX  */
  YYSYMBOL_TXS = 23,                       /* TXS  */
  YYSYMBOL_PHA = 24,                       /* PHA  */
  YYSYMBOL_PHP = 25,                       /* PHP  */
  YYSYMBOL_PLA = 26,                       /* PLA  */
  YYSYMBOL_PLP = 27,                       /* PLP  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_EOR = 29,                       /* EOR  */
  YYSYMBOL_ORA = 30,                       /* ORA  */
  YYSYMBOL_BIT = 31,                       /* BIT  */
  YYSYMBOL_ADC = 32,                       /* ADC  */
  YYSYMBOL_SBC = 33,                       /* SBC  */
  YYSYMBOL_CMP = 34,                       /* CMP  */
  YYSYMBOL_CPX = 35,                       /* CPX  */
  YYSYMBOL_CPY = 36,                       /* CPY  */
  YYSYMBOL_INC = 37,                       /* INC  */
  YYSYMBOL_INX = 38,                       /* INX  */
  YYSYMBOL_INY = 39,                       /* INY  */
  YYSYMBOL_DEC = 40,                       /* DEC  */
  YYSYMBOL_DEX = 41,                       /* DEX  */
  YYSYMBOL_DEY = 42,                       /* DEY  */
  YYSYMBOL_ASL = 43,                       /* ASL  */
  YYSYMBOL_LSR = 44,                       /* LSR  */
  YYSYMBOL_ROL = 45,                       /* ROL  */
  YYSYMBOL_ROR = 46,                       /* ROR  */
  YYSYMBOL_JMP = 47,                       /* JMP  */
  YYSYMBOL_JSR = 48,                       /* JSR  */
  YYSYMBOL_RTS = 49,                       /* RTS  */
  YYSYMBOL_BCC = 50,                       /* BCC  */
  YYSYMBOL_BCS = 51,                       /* BCS  */
  YYSYMBOL_BEQ = 52,                       /* BEQ  */
  YYSYMBOL_BMI = 53,                       /* BMI  */
  YYSYMBOL_BNE = 54,                       /* BNE  */
  YYSYMBOL_BPL = 55,                       /* BPL  */
  YYSYMBOL_BVC = 56,                       /* BVC  */
  YYSYMBOL_BVS = 57,                       /* BVS  */
  YYSYMBOL_CLC = 58,                       /* CLC  */
  YYSYMBOL_CLD = 59,                       /* CLD  */
  YYSYMBOL_CLI = 60,                       /* CLI  */
  YYSYMBOL_CLV = 61,                       /* CLV  */
  YYSYMBOL_SEC = 62,                       /* SEC  */
  YYSYMBOL_SED = 63,                       /* SED  */
  YYSYMBOL_SEI = 64,                       /* SEI  */
  YYSYMBOL_BRK = 65,                       /* BRK  */
  YYSYMBOL_NOP = 66,                       /* NOP  */
  YYSYMBOL_RTI = 67,                       /* RTI  */
  YYSYMBOL_SLO = 68,                       /* SLO  */
  YYSYMBOL_DCP = 69,                       /* DCP  */
  YYSYMBOL_RLA = 70,                       /* RLA  */
  YYSYMBOL_SRE = 71,                       /* SRE  */
  YYSYMBOL_LAX = 72,                       /* LAX  */
  YYSYMBOL_ISC = 73,                       /* ISC  */
  YYSYMBOL_74_ = 74,                       /* '='  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_76_ = 76,                       /* '#'  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '<'  */
  YYSYMBOL_80_ = 80,                       /* '>'  */
  YYSYMBOL_81_ = 81,                       /* '('  */
  YYSYMBOL_82_ = 82,                       /* ')'  */
  YYSYMBOL_83_x_ = 83,                     /* 'x'  */
  YYSYMBOL_84_y_ = 84,                     /* 'y'  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_program = 86,                   /* program  */
  YYSYMBOL_plist = 87,                     /* plist  */
  YYSYMBOL_dir = 88,                       /* dir  */
  YYSYMBOL_decl = 89,                      /* decl  */
  YYSYMBOL_section = 90,                   /* section  */
  YYSYMBOL_code = 91,                      /* code  */
  YYSYMBOL_data = 92,                      /* data  */
  YYSYMBOL_dlist = 93,                     /* dlist  */
  YYSYMBOL_inst = 94,                      /* inst  */
  YYSYMBOL_const = 95,                     /* const  */
  YYSYMBOL_expr = 96,                      /* expr  */
  YYSYMBOL_iexpr = 97                      /* iexpr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  94
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    76,     2,     2,     2,     2,
      81,    82,     2,    77,    75,    78,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      79,    74,    80,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      83,    84,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   122,   123,   128,   133,   138,   139,   144,
     149,   156,   159,   166,   172,   179,   185,   191,   198,   207,
     214,   223,   229,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   306,
     310,   314,   318,   322,   328,   332,   336,   340,   344,   348,
     352,   356,   362,   366,   370
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "DIRECTIVE",
  "NAME", "LABEL", "DATABYTES", "DATAWORDS", "HEXCONST", "BINCONST",
  "DECCONST", "LDA", "LDX", "LDY", "STA", "STX", "STY", "TAX", "TAY",
  "TXA", "TYA", "TSX", "TXS", "PHA", "PHP", "PLA", "PLP", "AND", "EOR",
  "ORA", "BIT", "ADC", "SBC", "CMP", "CPX", "CPY", "INC", "INX", "INY",
  "DEC", "DEX", "DEY", "ASL", "LSR", "ROL", "ROR", "JMP", "JSR", "RTS",
  "BCC", "BCS", "BEQ", "BMI", "BNE", "BPL", "BVC", "BVS", "CLC", "CLD",
  "CLI", "CLV", "SEC", "SED", "SEI", "BRK", "NOP", "RTI", "SLO", "DCP",
  "RLA", "SRE", "LAX", "ISC", "'='", "','", "'#'", "'+'", "'-'", "'<'",
  "'>'", "'('", "')'", "'x'", "'y'", "$accept", "program", "plist", "dir",
  "decl", "section", "code", "data", "dlist", "inst", "const", "expr",
  "iexpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      48,    39,   -69,   131,    10,    10,    32,    48,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    10,    10,
      10,    10,    10,    10,    10,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,   -75,   -75,    10,   -75,   -75,
      10,    10,    10,    10,    10,    38,   -75,    40,    52,    53,
      54,    55,    56,    63,    64,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,    10,    10,    10,    10,    10,
      10,   -75,   198,   -75,   -75,   -75,    10,    10,    10,    10,
      -5,   -75,   -74,    -5,   -75,   -75,   -75,   -75,   -75,   -74,
     -42,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -74,   -74,   -74,   -31,    10,    10,    10,   -66,   -75,   -74,
     -74,   -74,   -75,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     2,     3,     4,
       5,     6,    92,    93,    89,    90,    91,    11,     0,     0,
       0,     0,     0,     0,     0,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    56,     0,    58,    59,
      60,    62,    64,    66,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,    14,    13,    16,    15,    93,     0,     0,     0,     0,
      19,    95,    21,    20,     1,     7,     8,     9,    10,    12,
     102,    23,    24,    25,    26,    27,    28,    39,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    57,    61,    63,
      65,    67,    68,    69,    71,    72,    73,    74,    75,    76,
      77,    78,    40,    41,    45,    44,    43,    42,    18,    17,
      96,    99,   100,     0,     0,     0,     0,     0,   101,    22,
      97,    98,   103,   104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,    65,    66,     9,   -75,    -1,    69,   -11,
      74,    -4,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    82,    11,    90,    84,
      91,   100,   101
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      92,    92,    83,   145,   146,    18,    98,   102,   103,   104,
     105,   106,    81,    12,    99,    85,    97,   152,   153,    14,
      15,    16,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,    94,   147,   117,   145,   146,   118,   119,   120,
     121,   122,    12,   123,    13,   124,   145,   146,    14,    15,
      16,   148,     1,     2,     3,     4,     5,   125,   126,   127,
     128,   129,   132,   133,   134,   135,   136,   137,   130,   131,
     144,   139,    95,    96,    93,    17,     0,     0,     0,     0,
       0,   138,   140,   141,   142,   143,    86,     0,     0,    87,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
     149,   150,   151,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     4,     5,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80
};

static const yytype_int16 yycheck[] =
{
       4,     5,     3,    77,    78,    74,     7,    20,    21,    22,
      23,    24,     3,     3,    18,     5,     7,    83,    84,     9,
      10,    11,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,     0,    75,    47,    77,    78,    50,    51,    52,
      53,    54,     3,     5,     5,     5,    77,    78,     9,    10,
      11,    82,     4,     5,     6,     7,     8,     5,     5,     5,
       5,     5,    75,    76,    77,    78,    79,    80,     5,     5,
      75,    82,     7,     7,     5,     1,    -1,    -1,    -1,    -1,
      -1,    82,    86,    87,    88,    89,    76,    -1,    -1,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
     144,   145,   146,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     7,     8,    -1,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,    86,    87,    88,    89,
      90,    92,     3,     5,     9,    10,    11,    95,    74,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    90,    91,    92,    94,     5,    76,    79,    80,    81,
      93,    95,    96,    93,     0,    88,    89,    90,    92,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,     5,     5,     5,     5,     5,     5,     5,
       5,     5,    97,    97,    97,    97,    97,    97,    92,    94,
      96,    96,    96,    96,    75,    77,    78,    75,    82,    96,
      96,    96,    83,    84
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    89,    90,    90,    91,    91,    91,    91,    92,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     3,     2,     2,     1,     1,     2,     2,     2,
       2,     1,     3,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     2,     1,     1,
       1,     2,     1,     2,     1,     2,     1,     2,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     2,
       2,     3,     1,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* plist: decl  */
#line 124 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1702 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 5: /* plist: section  */
#line 129 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1711 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 6: /* plist: data  */
#line 134 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1720 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 8: /* plist: plist decl  */
#line 140 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1729 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 9: /* plist: plist section  */
#line 145 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1738 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 10: /* plist: plist data  */
#line 150 "asm6502.y"
        {
            root->children.push_back((yyvsp[0].node));
            (yyvsp[0].node)->parent = root;
        }
#line 1747 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 12: /* decl: NAME '=' expr  */
#line 160 "asm6502.y"
        {
            (yyval.node) = new DeclNode((yyvsp[-2].str), (yyvsp[0].node));
            (yyval.node)->lineNumber = (yylsp[-2]).first_line;
        }
#line 1756 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 13: /* section: LABEL code  */
#line 167 "asm6502.y"
        {
            (yyval.node) = new LabelNode((yyvsp[-1].str), (yyvsp[0].list));
            (yyval.node)->lineNumber = (yylsp[-1]).first_line;
            (yyvsp[0].list)->parent = (yyval.node);
        }
#line 1766 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 14: /* section: LABEL section  */
#line 173 "asm6502.y"
        {
            (yyval.node) = new LabelNode((yyvsp[-1].str), (yyvsp[0].node));
            (yyvsp[0].node)->parent = (yyval.node);
        }
#line 1775 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 15: /* code: inst  */
#line 180 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].instruction);
            (yyvsp[0].instruction)->parent = (yyval.list);
        }
#line 1785 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 16: /* code: data  */
#line 186 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].node);
            (yyvsp[0].node)->parent = (yyval.list);
        }
#line 1795 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 17: /* code: code inst  */
#line 192 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].instruction);
            (yyvsp[0].instruction)->parent = (yyval.list);
            (yyval.list)->next = (yyvsp[-1].list);
        }
#line 1806 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 18: /* code: code data  */
#line 199 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].node);
            (yyvsp[0].node)->parent = (yyval.list);
            (yyval.list)->next = (yyvsp[-1].list);
        }
#line 1817 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 19: /* data: DATABYTES dlist  */
#line 208 "asm6502.y"
        {
            (yyval.node) = new AstNode(AST_DATA8);
            (yyval.node)->lineNumber = (yylsp[-1]).first_line;
            (yyval.node)->value.node = (yyvsp[0].list);
            (yyvsp[0].list)->parent = (yyval.node);
        }
#line 1828 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 20: /* data: DATAWORDS dlist  */
#line 215 "asm6502.y"
        {
            (yyval.node) = new AstNode(AST_DATA16);
            (yyval.node)->lineNumber = (yylsp[-1]).first_line;
            (yyval.node)->value.node = (yyvsp[0].list);
            (yyvsp[0].list)->parent = (yyval.node);
        }
#line 1839 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 21: /* dlist: expr  */
#line 224 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].node);
            (yyvsp[0].node)->parent = (yyval.list);
        }
#line 1849 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 22: /* dlist: dlist ',' expr  */
#line 230 "asm6502.y"
        {
            (yyval.list) = new ListNode();
            (yyval.list)->value.node = (yyvsp[0].node);
            (yyvsp[0].node)->parent = (yyval.list);
            (yyval.list)->next = (yyvsp[-2].list);
        }
#line 1860 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 23: /* inst: LDA iexpr  */
#line 238 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), LDA, (yyvsp[0].node)); }
#line 1866 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 24: /* inst: LDX iexpr  */
#line 239 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), LDX, (yyvsp[0].node)); }
#line 1872 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 25: /* inst: LDY iexpr  */
#line 240 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), LDY, (yyvsp[0].node)); }
#line 1878 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 26: /* inst: STA iexpr  */
#line 241 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), STA, (yyvsp[0].node)); }
#line 1884 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 27: /* inst: STX iexpr  */
#line 242 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), STX, (yyvsp[0].node)); }
#line 1890 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 28: /* inst: STY iexpr  */
#line 243 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), STY, (yyvsp[0].node)); }
#line 1896 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 29: /* inst: TAX  */
#line 244 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TAX, NULL); }
#line 1902 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 30: /* inst: TAY  */
#line 245 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TAY, NULL); }
#line 1908 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 31: /* inst: TXA  */
#line 246 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TXA, NULL); }
#line 1914 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 32: /* inst: TYA  */
#line 247 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TYA, NULL); }
#line 1920 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 33: /* inst: TSX  */
#line 248 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TSX, NULL); }
#line 1926 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 34: /* inst: TXS  */
#line 249 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), TXS, NULL); }
#line 1932 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 35: /* inst: PHA  */
#line 250 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), PHA, NULL); }
#line 1938 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 36: /* inst: PHP  */
#line 251 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), PHP, NULL); }
#line 1944 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 37: /* inst: PLA  */
#line 252 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), PLA, NULL); }
#line 1950 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 38: /* inst: PLP  */
#line 253 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), PLP, NULL); }
#line 1956 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 39: /* inst: AND iexpr  */
#line 254 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), AND, (yyvsp[0].node)); }
#line 1962 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 40: /* inst: SLO iexpr  */
#line 255 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), SLO, (yyvsp[0].node)); }
#line 1968 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 41: /* inst: DCP iexpr  */
#line 256 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), DCP, (yyvsp[0].node)); }
#line 1974 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 42: /* inst: ISC iexpr  */
#line 257 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ISC, (yyvsp[0].node)); }
#line 1980 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 43: /* inst: LAX iexpr  */
#line 258 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), LAX, (yyvsp[0].node)); }
#line 1986 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 44: /* inst: SRE iexpr  */
#line 259 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), SRE, (yyvsp[0].node)); }
#line 1992 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 45: /* inst: RLA iexpr  */
#line 260 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), RLA, (yyvsp[0].node)); }
#line 1998 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 46: /* inst: EOR iexpr  */
#line 261 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), EOR, (yyvsp[0].node)); }
#line 2004 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 47: /* inst: ORA iexpr  */
#line 262 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ORA, (yyvsp[0].node)); }
#line 2010 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 48: /* inst: BIT iexpr  */
#line 263 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BIT, (yyvsp[0].node)); }
#line 2016 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 49: /* inst: ADC iexpr  */
#line 264 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ADC, (yyvsp[0].node)); }
#line 2022 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 50: /* inst: SBC iexpr  */
#line 265 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), SBC, (yyvsp[0].node)); }
#line 2028 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 51: /* inst: CMP iexpr  */
#line 266 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), CMP, (yyvsp[0].node)); }
#line 2034 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 52: /* inst: CPX iexpr  */
#line 267 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), CPX, (yyvsp[0].node)); }
#line 2040 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 53: /* inst: CPY iexpr  */
#line 268 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), CPY, (yyvsp[0].node)); }
#line 2046 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 54: /* inst: INC iexpr  */
#line 269 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), INC, (yyvsp[0].node)); }
#line 2052 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 55: /* inst: INX  */
#line 270 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), INX, NULL); }
#line 2058 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 56: /* inst: INY  */
#line 271 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), INY, NULL); }
#line 2064 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 57: /* inst: DEC iexpr  */
#line 272 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), DEC, (yyvsp[0].node)); }
#line 2070 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 58: /* inst: DEX  */
#line 273 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), DEX, NULL); }
#line 2076 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 59: /* inst: DEY  */
#line 274 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), DEY, NULL); }
#line 2082 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 60: /* inst: ASL  */
#line 275 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), ASL, NULL); }
#line 2088 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 61: /* inst: ASL iexpr  */
#line 276 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ASL, (yyvsp[0].node)); }
#line 2094 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 62: /* inst: LSR  */
#line 277 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), LSR, NULL); }
#line 2100 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 63: /* inst: LSR iexpr  */
#line 278 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), LSR, (yyvsp[0].node)); }
#line 2106 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 64: /* inst: ROL  */
#line 279 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), ROL, NULL); }
#line 2112 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 65: /* inst: ROL iexpr  */
#line 280 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ROL, (yyvsp[0].node)); }
#line 2118 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 66: /* inst: ROR  */
#line 281 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), ROR, NULL); }
#line 2124 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 67: /* inst: ROR iexpr  */
#line 282 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), ROR, (yyvsp[0].node)); }
#line 2130 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 68: /* inst: JMP iexpr  */
#line 283 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), JMP, (yyvsp[0].node)); }
#line 2136 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 69: /* inst: JSR NAME  */
#line 284 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), JSR, (yyvsp[0].str)); }
#line 2142 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 70: /* inst: RTS  */
#line 285 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), RTS, NULL); }
#line 2148 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 71: /* inst: BCC NAME  */
#line 286 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BCC, (yyvsp[0].str)); }
#line 2154 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 72: /* inst: BCS NAME  */
#line 287 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BCS, (yyvsp[0].str)); }
#line 2160 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 73: /* inst: BEQ NAME  */
#line 288 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BEQ, (yyvsp[0].str)); }
#line 2166 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 74: /* inst: BMI NAME  */
#line 289 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BMI, (yyvsp[0].str)); }
#line 2172 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 75: /* inst: BNE NAME  */
#line 290 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BNE, (yyvsp[0].str)); }
#line 2178 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 76: /* inst: BPL NAME  */
#line 291 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BPL, (yyvsp[0].str)); }
#line 2184 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 77: /* inst: BVC NAME  */
#line 292 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BVC, (yyvsp[0].str)); }
#line 2190 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 78: /* inst: BVS NAME  */
#line 293 "asm6502.y"
                { INST((yylsp[-1]), (yyval.instruction), BVS, (yyvsp[0].str)); }
#line 2196 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 79: /* inst: CLC  */
#line 294 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), CLC, NULL); }
#line 2202 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 80: /* inst: CLD  */
#line 295 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), CLD, NULL); }
#line 2208 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 81: /* inst: CLI  */
#line 296 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), CLI, NULL); }
#line 2214 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 82: /* inst: CLV  */
#line 297 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), CLV, NULL); }
#line 2220 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 83: /* inst: SEC  */
#line 298 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), SEC, NULL); }
#line 2226 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 84: /* inst: SED  */
#line 299 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), SED, NULL); }
#line 2232 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 85: /* inst: SEI  */
#line 300 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), SEI, NULL); }
#line 2238 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 86: /* inst: BRK  */
#line 301 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), BRK, NULL); }
#line 2244 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 87: /* inst: NOP  */
#line 302 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), NOP, NULL); }
#line 2250 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 88: /* inst: RTI  */
#line 303 "asm6502.y"
                { INST((yylsp[0]), (yyval.instruction), RTI, NULL); }
#line 2256 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 89: /* const: HEXCONST  */
#line 307 "asm6502.y"
        {
            (yyval.str) = (yyvsp[0].str);
        }
#line 2264 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 90: /* const: BINCONST  */
#line 311 "asm6502.y"
        {
            (yyval.str) = (yyvsp[0].str);
        }
#line 2272 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 91: /* const: DECCONST  */
#line 315 "asm6502.y"
        {
            (yyval.str) = (yyvsp[0].str);
        }
#line 2280 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 92: /* const: STRING  */
#line 319 "asm6502.y"
        {
            (yyval.str) = (yyvsp[0].str);
        }
#line 2288 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 93: /* const: NAME  */
#line 323 "asm6502.y"
        {
            (yyval.str) = (yyvsp[0].str);
        }
#line 2296 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 94: /* expr: NAME  */
#line 329 "asm6502.y"
        {
            (yyval.node) = new AstNode(AST_NAME, (yyvsp[0].str));
        }
#line 2304 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 95: /* expr: const  */
#line 333 "asm6502.y"
        {
            (yyval.node) = new AstNode(AST_CONST, (yyvsp[0].str));
        }
#line 2312 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 96: /* expr: '#' expr  */
#line 337 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_IMMEDIATE, (yyvsp[0].node));
        }
#line 2320 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 97: /* expr: expr '+' expr  */
#line 341 "asm6502.y"
        {
            (yyval.node) = new BinaryNode(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 2328 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 98: /* expr: expr '-' expr  */
#line 345 "asm6502.y"
        {
            (yyval.node) = new BinaryNode(AST_SUBTRACT, (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 2336 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 99: /* expr: '<' expr  */
#line 349 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_LOBYTE, (yyvsp[0].node));
        }
#line 2344 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 100: /* expr: '>' expr  */
#line 353 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_HIBYTE, (yyvsp[0].node));
        }
#line 2352 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 101: /* expr: '(' expr ')'  */
#line 357 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_INDIRECT, (yyvsp[-1].node));
        }
#line 2360 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 102: /* iexpr: expr  */
#line 363 "asm6502.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 2368 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 103: /* iexpr: expr ',' 'x'  */
#line 367 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_INDEXED_X, (yyvsp[-2].node));
        }
#line 2376 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;

  case 104: /* iexpr: expr ',' 'y'  */
#line 371 "asm6502.y"
        {
            (yyval.node) = new UnaryNode(AST_INDEXED_Y, (yyvsp[-2].node));
        }
#line 2384 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"
    break;


#line 2388 "/home/jbhall/software_build/codegen_6502/test/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 376 "asm6502.y"


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("usage: codegen <INPUT ASM FILE> <OUTPUT ROOT DIRECTORY>\n");
        exit(1);
    }

    root = new RootNode();
    
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    
    cleanupAst(root);
    
    /*
    for (std::list<AstNode*>::iterator it = root->children.begin(); it != root->children.end(); ++it)
    {
        AstNode* node = (*it);
        printNode(node);
    }
    */

    Translator translator(argv[1], root);

    std::string outputDir(argv[2]);

    std::string sourceFilePath = outputDir + "/source/SMB/SMB.cpp";
    std::ofstream sourceFile(sourceFilePath.c_str());
    sourceFile << translator.getSourceOutput();

    std::string dataFilePath = outputDir + "/source/SMB/SMBData.cpp";
    std::ofstream dataFile(dataFilePath.c_str());
    dataFile << translator.getDataOutput();

    std::string dataHeaderFilePath = outputDir + "/source/SMB/SMBDataPointers.hpp";
    std::ofstream dataHeaderFile(dataHeaderFilePath.c_str());
    dataHeaderFile << translator.getDataHeaderOutput();

    std::string constantHeaderFilePath = outputDir + "/source/SMB/SMBConstants.hpp";
    std::ofstream constantHeaderFile(constantHeaderFilePath.c_str());
    constantHeaderFile << translator.getConstantHeaderOutput();
    
    return 0;
}

int countAstDepth(AstNode* node) {
    if (!node) return 0;
    
    int max_depth = 0;
    
    // For different node types
    if (node->type == AST_ROOT) {
        RootNode* root_node = (RootNode*)node;
        for (std::list<AstNode*>::iterator it = root_node->children.begin(); 
             it != root_node->children.end(); ++it) {
            int depth = countAstDepth(*it);
            if (depth > max_depth) max_depth = depth;
        }
    }
    else if (node->type == AST_LABEL) {
        // Fix: LabelNode doesn't have a 'code' member
        // Access the label's children in a way that matches your actual structure
        // This is a placeholder - adjust based on how LabelNode actually stores its children
        LabelNode* label_node = (LabelNode*)node;
        if (label_node->value.node) {
            int depth = countAstDepth(label_node->value.node);
            if (depth > max_depth) max_depth = depth;
        }
    }
    else if (node->type == AST_LIST) {
        ListNode* list_node = (ListNode*)node;
        if (list_node->value.node) {
            int depth = countAstDepth(list_node->value.node);
            if (depth > max_depth) max_depth = depth;
        }
        
        if (list_node->next) {
            int depth = countAstDepth(list_node->next);
            if (depth > max_depth) max_depth = depth;
        }
    }
    
    return max_depth + 1;
}

void yyerror(const char* s)
{
    extern char* yytext; // Add this declaration to access yytext in this scope
    
    fprintf(stderr, "\033[1;31mParse error at line %d:\033[0m %s\n", yylineno, s);
    
    // Print code context around the error
    if (yyin) {
        char buffer[256];
        long current_pos = ftell(yyin);
        
        // Go back to beginning of the file
        fseek(yyin, 0, SEEK_SET);
        
        // Read file line by line to get error context
        int line_count = 0;
        while (fgets(buffer, sizeof(buffer), yyin) && line_count <= yylineno) {
            line_count++;
            
            // Print lines around the error
            if (line_count >= yylineno - 2 && line_count <= yylineno + 2) {
                fprintf(stderr, "%s%4d: %s%s", 
                        (line_count == yylineno) ? "\033[1;33m> " : "  ", 
                        line_count, 
                        buffer,
                        (line_count == yylineno) ? "\033[0m" : "");
                
                // If this is the error line and doesn't end with newline, add one
                if (line_count == yylineno && buffer[strlen(buffer)-1] != '\n') {
                    fprintf(stderr, "\n");
                }
            }
        }
        
        // Restore file position
        fseek(yyin, current_pos, SEEK_SET);
    }
    
    // Print parser state information
    fprintf(stderr, "\nParser state dump:\n");
    fprintf(stderr, "- Current token: %s\n", yytext ? yytext : "<unknown>");
    
    // Print information about the parsed AST so far
    if (root && !root->children.empty()) {
        AstNode* lastNode = root->children.back();
        fprintf(stderr, "- Last node type: %d\n", lastNode->type);
        
        // Since we don't know the exact structure, let's just print the node type
        // without trying to access specific members
        fprintf(stderr, "- Last node line number: %d\n", lastNode->lineNumber);
    } else {
        fprintf(stderr, "- No nodes parsed yet\n");
    }
    
    // Print AST depth if available
    fprintf(stderr, "- AST nodes: %lu\n", root ? root->children.size() : 0);
    
    // Add suggestion based on error message
    if (strstr(s, "syntax error")) {
        fprintf(stderr, "\nPossible causes:\n");
        fprintf(stderr, "- Missing operand or incorrect addressing mode\n");
        fprintf(stderr, "- Unrecognized instruction or directive\n");
        fprintf(stderr, "- Mismatched parentheses or incorrect expression syntax\n");
    } else if (strstr(s, "expected")) {
        fprintf(stderr, "\nSyntax error details:\n");
        fprintf(stderr, "- Expected a specific token or production rule\n");
        fprintf(stderr, "- Check the grammar definition for the correct syntax\n");
    }
    
    exit(-1);
}
