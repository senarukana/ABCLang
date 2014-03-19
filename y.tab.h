/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     WHILE = 265,
     FOR = 266,
     RETURN = 267,
     BREAK = 268,
     CONTINUE = 269,
     NULL_T = 270,
     INCR = 271,
     DECR = 272,
     LP = 273,
     RP = 274,
     LB = 275,
     RB = 276,
     LC = 277,
     RC = 278,
     DOT = 279,
     SEMICOLON = 280,
     COMMA = 281,
     ASSIGN = 282,
     LOGICAL_AND = 283,
     LOGICAL_OR = 284,
     EQ = 285,
     NE = 286,
     GT = 287,
     GE = 288,
     LT = 289,
     LE = 290,
     ADD = 291,
     SUB = 292,
     MUL = 293,
     DIV = 294,
     MOD = 295,
     TRUE_T = 296,
     FALSE_T = 297
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
#define WHILE 265
#define FOR 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define NULL_T 270
#define INCR 271
#define DECR 272
#define LP 273
#define RP 274
#define LB 275
#define RB 276
#define LC 277
#define RC 278
#define DOT 279
#define SEMICOLON 280
#define COMMA 281
#define ASSIGN 282
#define LOGICAL_AND 283
#define LOGICAL_OR 284
#define EQ 285
#define NE 286
#define GT 287
#define GE 288
#define LT 289
#define LE 290
#define ADD 291
#define SUB 292
#define MUL 293
#define DIV 294
#define MOD 295
#define TRUE_T 296
#define FALSE_T 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 9 "abclang.y"
{
    char            *identifier;
    ABC_Char        *string;
    int             int_val;
    double          double_val;
    Expression      *expression;
    ArgumentList    *arg_list;
    ParameterList   *param_list;
    ExpressionList  *expression_list;
    Statement       *statement;
    StatementList   *statement_list;
    Block           *block;
    ElseIfList      *elseif;
}
/* Line 1529 of yacc.c.  */
#line 148 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

