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
/* Line 1529 of yacc.c.  */
#line 150 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

