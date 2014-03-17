/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LITERAL = 258,
     DOUBLE_LITERAL = 259,
     STRING_LITERAL = 260,
     IDENTIFIER = 261,
     FUNCTION = 262,
     IF = 263,
     ELSE = 264,
     ELSEIF = 265,
     WHILE = 266,
     FOR = 267,
     RETURN_T = 268,
     BREAK = 269,
     CONTINUE = 270,
     NULL_T = 271,
     INCR = 272,
     DECR = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     DOT = 280,
     SEMICOLON = 281,
     COMMA = 282,
     ASSIGN = 283,
     LOGICAL_AND = 284,
     LOGICAL_OR = 285,
     EQ = 286,
     NE = 287,
     GT = 288,
     GE = 289,
     LT = 290,
     LE = 291,
     ADD = 292,
     SUB = 293,
     MUL = 294,
     DIV = 295,
     MOD = 296,
     TRUE_T = 297,
     FALSE_T = 298
   };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define DOUBLE_LITERAL 259
#define STRING_LITERAL 260
#define IDENTIFIER 261
#define FUNCTION 262
#define IF 263
#define ELSE 264
#define ELSEIF 265
#define WHILE 266
#define FOR 267
#define RETURN_T 268
#define BREAK 269
#define CONTINUE 270
#define NULL_T 271
#define INCR 272
#define DECR 273
#define LP 274
#define RP 275
#define LB 276
#define RB 277
#define LC 278
#define RC 279
#define DOT 280
#define SEMICOLON 281
#define COMMA 282
#define ASSIGN 283
#define LOGICAL_AND 284
#define LOGICAL_OR 285
#define EQ 286
#define NE 287
#define GT 288
#define GE 289
#define LT 290
#define LE 291
#define ADD 292
#define SUB 293
#define MUL 294
#define DIV 295
#define MOD 296
#define TRUE_T 297
#define FALSE_T 298




/* Copy the first part of user declarations.  */
#line 1 "abclang.y"

#include <stdio.h>
#include "abclang.h"   


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 6 "abclang.y"
{
    char            *identifier;
    char            *string_val;
    int             int_val;
    double          double_val;
    Expression      *expression;
    ArgumentList    *arg_list;
    ParameterList   *param_list;
    ExpressionList  *expression_list;
    IdentifierList  *identifier_list;
    Statement       *statement;
    StatementList   *statement_list;
    Block           *block;
}
/* Line 193 of yacc.c.  */
#line 202 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 215 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    19,    25,    27,
      31,    33,    37,    41,    44,    46,    49,    52,    54,    56,
      58,    60,    62,    64,    66,    69,    71,    75,    79,    85,
      90,    97,    99,   102,   107,   115,   119,   123,   126,   129,
     130,   132,   134,   136,   138,   142,   149,   155,   160,   164,
     166,   168,   172,   174,   178,   180,   184,   188,   190,   194,
     198,   202,   206,   208,   212,   216,   218,   222,   226,   230,
     232,   235,   238,   240,   243,   245,   250,   252,   254,   258,
     260,   262,   264,   266,   268,   270
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    45,    46,    -1,    47,    -1,
      52,    -1,     7,     6,    19,    49,    20,    50,    -1,     7,
       6,    19,    20,    50,    -1,    68,    -1,    48,    27,    68,
      -1,     6,    -1,    49,    27,     6,    -1,    23,    51,    24,
      -1,    23,    24,    -1,    52,    -1,    51,    52,    -1,    64,
      26,    -1,    53,    -1,    55,    -1,    58,    -1,    59,    -1,
      61,    -1,    62,    -1,    60,    -1,    54,    26,    -1,     6,
      -1,    54,    27,     6,    -1,     8,    68,    50,    -1,     8,
      68,    50,     9,    50,    -1,     8,    68,    50,    56,    -1,
       8,    68,    50,    56,     9,    50,    -1,    57,    -1,    56,
      57,    -1,     9,     8,    68,    50,    -1,    12,    63,    27,
      63,    27,    63,    50,    -1,    11,    68,    50,    -1,    13,
      68,    26,    -1,    14,    26,    -1,    15,    26,    -1,    -1,
      68,    -1,    65,    -1,    66,    -1,    67,    -1,     6,    28,
      68,    -1,    77,    25,     6,    19,    48,    20,    -1,    77,
      25,     6,    19,    20,    -1,     6,    19,    48,    20,    -1,
       6,    19,    20,    -1,    69,    -1,    70,    -1,    69,    30,
      70,    -1,    71,    -1,    70,    29,    71,    -1,    72,    -1,
      71,    31,    72,    -1,    71,    32,    72,    -1,    73,    -1,
      72,    33,    73,    -1,    72,    34,    73,    -1,    72,    35,
      73,    -1,    72,    36,    73,    -1,    74,    -1,    73,    37,
      74,    -1,    73,    38,    74,    -1,    75,    -1,    74,    39,
      75,    -1,    74,    40,    75,    -1,    74,    41,    75,    -1,
      76,    -1,    75,    17,    -1,    75,    18,    -1,    77,    -1,
      38,    77,    -1,    78,    -1,    77,    21,    68,    22,    -1,
      67,    -1,    66,    -1,    19,    68,    20,    -1,     6,    -1,
       3,    -1,     4,    -1,     5,    -1,    42,    -1,    43,    -1,
      16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    48,    48,    49,    52,    53,    60,    63,    68,    71,
      76,    79,    85,    88,    94,    97,   103,   106,   107,   108,
     109,   110,   111,   112,   116,   122,   125,   131,   134,   137,
     140,   146,   147,   152,   157,   162,   166,   170,   174,   180,
     183,   187,   188,   189,   193,   199,   202,   208,   211,   216,
     219,   220,   226,   227,   233,   234,   237,   243,   244,   247,
     250,   253,   259,   260,   263,   269,   270,   273,   276,   282,
     283,   286,   292,   293,   299,   300,   306,   307,   308,   311,
     314,   317,   320,   323,   326,   329
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DOUBLE_LITERAL",
  "STRING_LITERAL", "IDENTIFIER", "FUNCTION", "IF", "ELSE", "ELSEIF",
  "WHILE", "FOR", "RETURN_T", "BREAK", "CONTINUE", "NULL_T", "INCR",
  "DECR", "LP", "RP", "LB", "RB", "LC", "RC", "DOT", "SEMICOLON", "COMMA",
  "ASSIGN", "LOGICAL_AND", "LOGICAL_OR", "EQ", "NE", "GT", "GE", "LT",
  "LE", "ADD", "SUB", "MUL", "DIV", "MOD", "TRUE_T", "FALSE_T", "$accept",
  "translation_unit", "def_or_statement", "function_def", "argument_list",
  "parameter_list", "block", "statement_list", "statement",
  "global_statement", "identifier_list", "if_statement", "elseif_list",
  "elseif", "for_statement", "while_statement", "return_statement",
  "break_statement", "continue_statement", "expression_opt",
  "statement_expression", "assign_expression", "method_call_expression",
  "function_call_expression", "expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "add_sub_expression", "mul_div_mod_expression", "incr_decr_expression",
  "minus_expression", "postfix_expression", "primary_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    54,    55,    55,    55,
      55,    56,    56,    57,    58,    59,    60,    61,    62,    63,
      63,    64,    64,    64,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    71,    71,    71,    72,    72,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    75,
      75,    75,    76,    76,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     6,     5,     1,     3,
       1,     3,     3,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     5,     4,
       6,     1,     2,     4,     7,     3,     3,     2,     2,     0,
       1,     1,     1,     1,     3,     6,     5,     4,     3,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     2,     1,     4,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    80,    81,    82,    25,     0,     0,     0,    39,     0,
       0,     0,    85,     0,    83,    84,     0,     2,     4,     5,
      17,     0,    18,    19,    20,    23,    21,    22,     0,    41,
      77,    76,     0,    74,     0,     0,     0,    79,     0,    77,
      76,     0,    49,    50,    52,    54,    57,    62,    65,    69,
      72,     0,     0,    40,     0,    37,    38,     0,     1,     3,
      24,     0,    16,     0,     0,    48,     0,     8,    44,     0,
      73,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,    71,    35,    39,
      36,    78,    26,     0,     0,    47,     0,    10,     0,     0,
      13,     0,    14,     0,    29,    31,    51,    53,    55,    56,
      58,    59,    60,    61,    63,    64,    66,    67,    68,     0,
      75,     0,     9,     7,     0,     0,    12,    15,     0,    28,
       0,    32,    39,    46,     0,     6,    11,     0,    30,     0,
      45,    33,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    16,    17,    18,    66,    99,    72,   101,    19,    20,
      21,    22,   104,   105,    23,    24,    25,    26,    27,    52,
      28,    29,    39,    40,    53,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    33
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
     105,   -82,   -82,   -82,    44,    41,   172,   172,   172,   172,
     -15,    38,   -82,   172,   -82,   -82,    19,   -82,   -82,   -82,
     -82,    28,   -82,   -82,   -82,   -82,   -82,   -82,    48,   -82,
      51,    58,    -9,   -82,    40,   172,    72,    74,   189,   -82,
     -82,    81,    77,    85,    39,    53,    43,   -26,    82,   -82,
      -9,    81,    96,   -82,   103,   -82,   -82,   119,   -82,   -82,
     -82,   134,   -82,   172,   136,   -82,   -10,   -82,   -82,    30,
      -9,   122,   135,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   -82,   -82,   -82,   172,
     -82,   -82,   -82,   121,   126,   -82,   172,   -82,    81,    21,
     -82,   147,   -82,    29,   140,   -82,    85,    39,    53,    53,
      43,    43,    43,    43,   -26,   -26,    82,    82,    82,   127,
     -82,   164,   -82,   -82,    81,   150,   -82,   -82,   172,   -82,
      29,   -82,   172,   -82,    22,   -82,   -82,    81,   -82,    81,
     -82,   -82,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   141,   -82,    52,   -82,   -45,   -82,   -62,   -82,
     -82,   -82,   -82,    68,   -82,   -82,   -82,   -82,   -82,   -81,
     -82,   -82,     4,     5,    -6,   -82,   101,   107,    26,    18,
      50,   -17,   -82,     2,   -82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -80
static const yytype_int16 yytable[] =
{
      41,    51,    32,    54,    30,    31,    88,    57,   119,   102,
      95,    55,    63,    83,    84,    85,    64,    96,    32,    58,
      30,    31,     1,     2,     3,     4,     5,     6,    67,    68,
       7,     8,     9,    10,    11,    12,    97,   128,    13,   127,
      70,   124,   140,     1,     2,     3,    37,    36,   125,    96,
      98,   139,    71,   123,    60,    61,    12,    93,   129,    13,
      65,    14,    15,    34,    56,   -79,   116,   117,   118,   -79,
      75,    76,    35,    32,    62,    30,    31,   -42,    38,   135,
      81,    82,    14,    15,   -43,   138,    77,    78,    79,    80,
     122,    69,   141,    34,   142,   110,   111,   112,   113,    86,
      87,   108,   109,    32,    71,    30,    31,    73,     1,     2,
       3,     4,     5,     6,    74,    67,     7,     8,     9,    10,
      11,    12,   137,    89,    13,     1,     2,     3,     4,    90,
       6,   114,   115,     7,     8,     9,    10,    11,    12,    91,
      92,    13,    94,   120,   103,   121,   100,    14,    15,   130,
       1,     2,     3,     4,   132,     6,   136,    59,     7,     8,
       9,    10,    11,    12,    14,    15,    13,     1,     2,     3,
      37,   126,   131,   134,   106,     1,     2,     3,    37,     0,
      12,   107,     0,    13,   133,     0,     0,     0,    12,    14,
      15,    13,     1,     2,     3,    37,     0,     0,     0,     0,
       0,     0,    38,     0,     0,    12,    14,    15,    13,     0,
      38,     0,     0,     0,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15
};

static const yytype_int16 yycheck[] =
{
       6,     7,     0,     9,     0,     0,    51,    13,    89,    71,
      20,    26,    21,    39,    40,    41,    25,    27,    16,     0,
      16,    16,     3,     4,     5,     6,     7,     8,    34,    35,
      11,    12,    13,    14,    15,    16,     6,     8,    19,   101,
      38,    20,    20,     3,     4,     5,     6,     6,    27,    27,
      20,   132,    23,    98,    26,    27,    16,    63,   103,    19,
      20,    42,    43,    19,    26,    21,    83,    84,    85,    25,
      31,    32,    28,    71,    26,    71,    71,    26,    38,   124,
      37,    38,    42,    43,    26,   130,    33,    34,    35,    36,
      96,    19,   137,    19,   139,    77,    78,    79,    80,    17,
      18,    75,    76,   101,    23,   101,   101,    30,     3,     4,
       5,     6,     7,     8,    29,   121,    11,    12,    13,    14,
      15,    16,   128,    27,    19,     3,     4,     5,     6,    26,
       8,    81,    82,    11,    12,    13,    14,    15,    16,    20,
       6,    19,     6,    22,     9,    19,    24,    42,    43,     9,
       3,     4,     5,     6,    27,     8,     6,    16,    11,    12,
      13,    14,    15,    16,    42,    43,    19,     3,     4,     5,
       6,    24,   104,   121,    73,     3,     4,     5,     6,    -1,
      16,    74,    -1,    19,    20,    -1,    -1,    -1,    16,    42,
      43,    19,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    16,    42,    43,    19,    -1,
      38,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    12,    13,
      14,    15,    16,    19,    42,    43,    45,    46,    47,    52,
      53,    54,    55,    58,    59,    60,    61,    62,    64,    65,
      66,    67,    77,    78,    19,    28,     6,     6,    38,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    68,    63,    68,    68,    26,    26,    68,     0,    46,
      26,    27,    26,    21,    25,    20,    48,    68,    68,    19,
      77,    23,    50,    30,    29,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    17,    18,    50,    27,
      26,    20,     6,    68,     6,    20,    27,     6,    20,    49,
      24,    51,    52,     9,    56,    57,    70,    71,    72,    72,
      73,    73,    73,    73,    74,    74,    75,    75,    75,    63,
      22,    19,    68,    50,    20,    27,    24,    52,     8,    50,
       9,    57,    27,    20,    48,    50,     6,    68,    50,    63,
      20,    50,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 53 "abclang.y"
    {
            ABC_Interpreter *inter = abc_get_interpreter();
            inter->statement_list = abc_chain_statement_list(
                inter->statement_list, (yyvsp[(1) - (1)].statement));
        }
    break;

  case 6:
#line 60 "abclang.y"
    {
            abc_create_function((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].param_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 7:
#line 63 "abclang.y"
    {
            abc_create_function((yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(5) - (5)].block));
        }
    break;

  case 8:
#line 68 "abclang.y"
    {
            (yyval.arg_list) = abc_create_argument((yyvsp[(1) - (1)].expression));
        }
    break;

  case 9:
#line 71 "abclang.y"
    {
            (yyval.arg_list) = abc_chain_argument((yyvsp[(1) - (3)].arg_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 10:
#line 76 "abclang.y"
    {
            (yyval.param_list) = abc_create_parameter((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 11:
#line 79 "abclang.y"
    {
            (yyval.param_list) = abc_chain_parameter((yyvsp[(1) - (3)].param_list), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 12:
#line 85 "abclang.y"
    {
            (yyval.block) = abc_create_block((yyvsp[(2) - (3)].statement_list));
        }
    break;

  case 13:
#line 88 "abclang.y"
    {
            (yyval.block) = abc_create_block(NULL);
        }
    break;

  case 14:
#line 94 "abclang.y"
    {
            (yyval.statement_list) = abc_create_statment_list((yyvsp[(1) - (1)].statement));
        }
    break;

  case 15:
#line 97 "abclang.y"
    {
            (yyval.statement_list) = abc_chain_statement_list((yyvsp[(1) - (2)].statement_list), (yyvsp[(2) - (2)].statement));
        }
    break;

  case 16:
#line 103 "abclang.y"
    {
            (yyval.statement) = abc_create_expression_statement((yyvsp[(1) - (2)].expression));
        }
    break;

  case 24:
#line 116 "abclang.y"
    {
            (yyval.statement) = abc_create_global_statement((yyvsp[(1) - (2)].identifier_list));
        }
    break;

  case 25:
#line 122 "abclang.y"
    {
            (yyval.identifier_list) = abc_create_global_identifier((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 26:
#line 125 "abclang.y"
    {
            (yyval.identifier_list) = abc_chain_global_identifier((yyvsp[(1) - (3)].identifier_list), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 27:
#line 131 "abclang.y"
    {
            (yyval.statement) = abc_create_if_statement((yyvsp[(2) - (3)].expression), (yyvsp[(3) - (3)].block), NULL, NULL);    
        }
    break;

  case 28:
#line 134 "abclang.y"
    {
            (yyval.statement) = abc_create_if_statement((yyvsp[(2) - (5)].expression), (yyvsp[(3) - (5)].block), (yyvsp[(5) - (5)].block));
        }
    break;

  case 29:
#line 137 "abclang.y"
    {
            (yyval.statement) = abc_create_if_statement((yyvsp[(2) - (4)].expression), (yyvsp[(3) - (4)].block), (yyvsp[(4) - (4)].elseif), NULL);
        }
    break;

  case 30:
#line 140 "abclang.y"
    {
            (yyval.statement) = abc_create_if_statement((yyvsp[(2) - (6)].expression), (yyvsp[(3) - (6)].block), (yyvsp[(4) - (6)].elseif), (yyvsp[(6) - (6)].block));
        }
    break;

  case 32:
#line 147 "abclang.y"
    {
            (yyval.elseif) = abc_chain_elseif((yyvsp[(1) - (2)].elseif), (yyvsp[(2) - (2)].elseif));
        }
    break;

  case 33:
#line 152 "abclang.y"
    {
            (yyval.elseif) = abc_create_elseif((yyvsp[(3) - (4)].expression), (yyvsp[(4) - (4)].block));
        }
    break;

  case 34:
#line 157 "abclang.y"
    {
        (yyval.statement) = abc_create_for_statement((yyvsp[(2) - (7)].expression), (yyvsp[(4) - (7)].expression), (yyvsp[(6) - (7)].expression), (yyvsp[(7) - (7)].block));
    }
    break;

  case 35:
#line 162 "abclang.y"
    {
        (yyval.statement) = abc_create_while_statement((yyvsp[(2) - (3)].expression), (yyvsp[(3) - (3)].block)); 
    }
    break;

  case 36:
#line 166 "abclang.y"
    {
        (yyval.statement) = abc_create_return_statement((yyvsp[(2) - (3)].expression));
    }
    break;

  case 37:
#line 170 "abclang.y"
    {
        (yyval.statement) = abc_create_break_statement();
    }
    break;

  case 38:
#line 174 "abclang.y"
    {
        (yyval.statement) = abc_create_continue_statement();
    }
    break;

  case 39:
#line 180 "abclang.y"
    {
            (yyval.expression) = NULL;
        }
    break;

  case 44:
#line 193 "abclang.y"
    {
            (yyval.expression) = abc_create_assign_expression((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 45:
#line 199 "abclang.y"
    {
            (yyval.expression) = abc_create_method_call_expression((yyvsp[(1) - (6)].expression), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].arg_list));
        }
    break;

  case 46:
#line 202 "abclang.y"
    {
            (yyval.expression) = abc_create_method_call_expression((yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].identifier), NULL);
        }
    break;

  case 47:
#line 208 "abclang.y"
    {
            (yyval.expression) = abc_create_funcion_call_expression((yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].arg_list));
        }
    break;

  case 48:
#line 211 "abclang.y"
    {
            (yyval.expression) = abc_create_funcion_call_expression((yyvsp[(1) - (3)].identifier), NULL);
        }
    break;

  case 51:
#line 220 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(LOGICAL_OR_EXPRESSION ,(yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 53:
#line 227 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(LOGICAL_AND_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 55:
#line 234 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(EQUAL_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 56:
#line 237 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(NOT_EQUAL_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 58:
#line 244 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(GT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 59:
#line 247 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(GE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 60:
#line 250 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(LT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 61:
#line 253 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(LE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 63:
#line 260 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(ADD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 64:
#line 263 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(SUB_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 66:
#line 270 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(MUL_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 67:
#line 273 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(DIV_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 68:
#line 276 "abclang.y"
    {
            (yyval.expression) = abc_create_binary_expression(MOD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 70:
#line 283 "abclang.y"
    {
            (yyval.expression) = abc_create_singular_expression(INCR_EXPRESSION, (yyvsp[(1) - (2)].expression));
        }
    break;

  case 71:
#line 286 "abclang.y"
    {
            (yyval.expression) = abc_create_singular_expression(DECR_EXPRESSION, (yyvsp[(1) - (2)].expression));
        }
    break;

  case 73:
#line 293 "abclang.y"
    {
            (yyval.expression) = abc_create_singular_expression(MINUS_EXPRESSION, (yyvsp[(2) - (2)].expression));
        }
    break;

  case 75:
#line 300 "abclang.y"
    {
            (yyval.expression) = abc_create_index_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression));
        }
    break;

  case 78:
#line 308 "abclang.y"
    {
            (yyval.expression) = (yyvsp[(2) - (3)].expression);
        }
    break;

  case 79:
#line 311 "abclang.y"
    {
            (yyval.expression) = abc_create_identifier_expression((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 80:
#line 314 "abclang.y"
    {
            (yyval.expression) = abc_create_int_expression((yyvsp[(1) - (1)].int_val));
        }
    break;

  case 81:
#line 317 "abclang.y"
    {
            (yyval.expression) = abc_create_double_expression((yyvsp[(1) - (1)].double_val));
        }
    break;

  case 82:
#line 320 "abclang.y"
    {
            (yyval.expression) = abc_create_string_expression((yyvsp[(1) - (1)].string_val));
        }
    break;

  case 83:
#line 323 "abclang.y"
    {
            (yyval.expression) = abc_create_boolean_expression(ABC_TRUE);
        }
    break;

  case 84:
#line 326 "abclang.y"
    {
            (yyval.expression) = abc_create_boolean_expression(ABC_FALSE);
        }
    break;

  case 85:
#line 329 "abclang.y"
    {
            (yyval.expression) = abc_create_null_expression();
        }
    break;


/* Line 1267 of yacc.c.  */
#line 1970 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 333 "abclang.y"

