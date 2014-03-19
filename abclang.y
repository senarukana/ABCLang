%{
#include <stdio.h>
#include "abclang.h"
#define YYDEBUG 1
%}  

%union {
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

%token <int_val>        INT_LITERAL
%token <double_val>     DOUBLE_LITERAL
%token <string>     STRING_LITERAL
%token <identifier>     IDENTIFIER

%token FUNCTION IF ELSE ELSEIF WHILE FOR RETURN BREAK CONTINUE NULL_T INCR DECR
        LP RP LB RB LC RC DOT SEMICOLON COMMA  
        ASSIGN LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T
%type   <param_list> parameter_list
%type   <arg_list> argument_list
%type   <expression> expression expression_opt
        statement_expression assign_expression function_call_expression method_call_expression 
        logical_and_expression logical_or_expression
        equality_expression relational_expression
        add_sub_expression mul_div_mod_expression incr_decr_expression 
        minus_expression postfix_expression primary_expression
%type   <statement> statement 
        if_statement while_statement for_statement
        return_statement break_statement continue_statement
%type   <statement_list> statement_list
%type   <block> block
%type   <elseif> elseif elseif_list
%%
translation_unit:
        def_or_statement
    |   translation_unit def_or_statement
    ;
def_or_statement:
        function_def 
    |   statement {
            ABC_Interpreter *inter = abc_get_interpreter();
            inter->statement_list = abc_chain_statement_list(
                inter->statement_list, $1);
            fprintf(stderr,"ok!\n");
        }
    ;
function_def:
        FUNCTION IDENTIFIER LP parameter_list RP block {
            abc_create_function($2, $4, $6);
        }
    |   FUNCTION IDENTIFIER LP RP block {
            abc_create_function($2, NULL, $5);
        }
    ;
argument_list:
        expression {
            $$ = abc_create_argument($1);
        }
    |   argument_list COMMA expression {
            $$ = abc_chain_argument($1, $3);
        }
    ;
parameter_list:
        IDENTIFIER {
            $$ = abc_create_parameter($1);
        }
    |   parameter_list COMMA IDENTIFIER{
            $$ = abc_chain_parameter($1, $3);
        }
    ;

block:
        LC statement_list RC {
            $$ = abc_create_block($2);
        }
    |   LC RC {
            $$ = abc_create_block(NULL);
        } 
    ;

statement_list: 
        statement {
            $$ = abc_create_statement_list($1);
        }
    |   statement_list statement {
            $$ = abc_chain_statement_list($1, $2);
        }
    ;

statement:
        statement_expression SEMICOLON {
            $$ = abc_create_expression_statement($1);
        } 
    |   if_statement
    |   for_statement
    |   while_statement
    |   break_statement
    |   continue_statement
    |   return_statement
    ;


if_statement:
        IF expression block {
            $$ = abc_create_if_statement($2, $3, NULL, NULL);    
        }
    |   IF expression block ELSE block {
            $$ = abc_create_if_statement($2, $3, NULL, $5);
        }
    |   IF expression block elseif_list {
            $$ = abc_create_if_statement($2, $3, $4, NULL);
        }
    |   IF expression block elseif_list ELSE block {
            $$ = abc_create_if_statement($2, $3, $4, $6);
        }
    ;

elseif_list:
        elseif 
    |   elseif_list elseif {
            $$ = abc_chain_elseif($1, $2);
        }
    ; 

elseif: ELSE IF expression block {
            $$ = abc_create_elseif($3, $4);
        }
    ; 

for_statement: FOR expression_opt COMMA expression_opt COMMA expression_opt block {
        $$ = abc_create_for_statement($2, $4, $6, $7);
    }
    ;

while_statement: WHILE expression block {
        $$ = abc_create_while_statement($2, $3); 
    }
    ;
return_statement: RETURN expression SEMICOLON {
        $$ = abc_create_return_statement($2);
    }
    ;
break_statement: BREAK SEMICOLON {
        $$ = abc_create_break_statement();
    }
    ;
continue_statement: CONTINUE SEMICOLON {
        $$ = abc_create_continue_statement();
    }
    ;

expression_opt:
        /* empty */ {
            $$ = NULL;
        }
    |   expression
    ;

statement_expression:
        assign_expression
    |   method_call_expression
    |   function_call_expression
    ;

assign_expression:
       expression ASSIGN expression {
            $$ = abc_create_assign_expression($1, $3);
        }
    ;

method_call_expression:
        postfix_expression DOT IDENTIFIER LP argument_list RP {
            $$ = abc_create_method_call_expression($1, $3, $5);
        }
    |   postfix_expression DOT IDENTIFIER LP RP {
            $$ = abc_create_method_call_expression($1, $3, NULL);
        }
    ;

function_call_expression:
        IDENTIFIER LP argument_list RP {
            $$ = abc_create_function_call_expression($1, $3);
        }
    |   IDENTIFIER LP RP {
            $$ = abc_create_function_call_expression($1, NULL);
        }
    ;

expression: logical_or_expression;

logical_or_expression:
        logical_and_expression
    |   logical_or_expression LOGICAL_OR logical_and_expression {
            $$ = abc_create_binary_expression(LOGICAL_OR_EXPRESSION ,$1, $3);
        }
    ;

logical_and_expression:
        equality_expression
    |   logical_and_expression LOGICAL_AND equality_expression {
            $$ = abc_create_binary_expression(LOGICAL_AND_EXPRESSION, $1, $3);
        }
    ;

equality_expression:
        relational_expression
    |   equality_expression EQ relational_expression {
            $$ = abc_create_binary_expression(EQUAL_EXPRESSION, $1, $3);
        }
    |   equality_expression NE relational_expression {
            $$ = abc_create_binary_expression(NOT_EQUAL_EXPRESSION, $1, $3);
        }
    ;

relational_expression:
        add_sub_expression
    |   relational_expression GT add_sub_expression {
            $$ = abc_create_binary_expression(GT_EXPRESSION, $1, $3);
        }
    |   relational_expression GE add_sub_expression {
            $$ = abc_create_binary_expression(GE_EXPRESSION, $1, $3);
        }
    |   relational_expression LT add_sub_expression {
            $$ = abc_create_binary_expression(LT_EXPRESSION, $1, $3);
        }
    |   relational_expression LE add_sub_expression {
            $$ = abc_create_binary_expression(LE_EXPRESSION, $1, $3);
        }
    ;

add_sub_expression:
        mul_div_mod_expression
    |   add_sub_expression ADD mul_div_mod_expression {
            $$ = abc_create_binary_expression(ADD_EXPRESSION, $1, $3);
        }
    |   add_sub_expression SUB mul_div_mod_expression {
            $$ = abc_create_binary_expression(SUB_EXPRESSION, $1, $3);
        }
    ;

mul_div_mod_expression:
        incr_decr_expression 
    |   mul_div_mod_expression MUL incr_decr_expression {
            $$ = abc_create_binary_expression(MUL_EXPRESSION, $1, $3);
        }
    |   mul_div_mod_expression DIV incr_decr_expression {
            $$ = abc_create_binary_expression(DIV_EXPRESSION, $1, $3);
        }
    |   mul_div_mod_expression MOD incr_decr_expression {
            $$ = abc_create_binary_expression(MOD_EXPRESSION, $1, $3);
        }
    ;

incr_decr_expression:
        minus_expression
    |   incr_decr_expression INCR {
            $$ = abc_create_singular_expression(INCREMENT_EXPRESSION, $1);
        }
    |   incr_decr_expression DECR {
            $$ = abc_create_singular_expression(DECREMENT_EXPRESSION, $1);
        }
    ;

minus_expression:
        postfix_expression
    |   SUB postfix_expression {
            $$ = abc_create_singular_expression(MINUS_EXPRESSION, $2);
        }
    ;

postfix_expression:
        primary_expression
    |   postfix_expression LB expression RB {
            $$ = abc_create_index_expression($1, $3);
        }   
    ;

primary_expression:
        function_call_expression
    |   method_call_expression
    |   LP expression RP {
            $$ = $2;
        }
    |   IDENTIFIER {
            $$ = abc_create_identifier_expression($1);
        }
    |   INT_LITERAL {
            $$ = abc_create_int_expression($1);
        }
    |   DOUBLE_LITERAL {
            $$ = abc_create_double_expression($1);
        }
    |   STRING_LITERAL {
            $$ = abc_create_string_expression($1);
        }
    |   TRUE_T {
            $$ = abc_create_boolean_expression(ABC_True);
        }
    |   FALSE_T {
            $$ = abc_create_boolean_expression(ABC_False);
        }
    |   NULL_T {
            $$ = abc_create_null_expression();
        }
    ;
%%