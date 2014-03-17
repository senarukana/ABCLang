%{
#include <stdio.h>
#include "y.tab.h"
#include "abclang.h"

int yywrap() {
    return 1;
}

static void increment_line_number() {
    abc_get_intrepreter()->line_number++;
}
%}

%start COMMENT_STATE STRING_STATE

%%
<INITIAL>"def"          return FUNCTION;
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>"elseif"       return ELSEIF;
<INITIAL>"for"          return FOR;
<INITIAL>"while"        return WHILE;
<INITIAL>"return"       return RETURN;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"null"         return NULL_T;
<INITIAL>"true"         return TRUE_T;
<INITIAL>"false"        return FALSE_T; 
<INITIAL>"("            return LP;
<INITIAL>")"            return RP;
<INITIAL>"{"            return LC;
<INITIAL>"}"            return RC;
<INITIAL>"["            return LB;
<INITIAL>"]"            return RB;
<INITIAL>"+"            return ADD;
<INITIAL>"-"            return SUB;
<INITIAL>"*"            return MUL;
<INITIAL>"/"            return DIV;
<INITIAL>"++"           return INCR;
<INITIAL>"--"           return DECR;
<INITIAL>"%"            return MOD;
<INITIAL>";"            return SEMICOLON;
<INITIAL>","            return COMMA;
<INITIAL>"."            return DOT;
<INITIAL>"&&"           return LOGICAL_AND;
<INITIAL>"||"           return LOGICAL_OR;
<INITIAL>"="            return ASSIGN;
<INITIAL>"=="           return EQ;
<INITIAL>"!="           return NE;
<INITIAL>">"            return GT;
<INITIAL>">="           return GE;
<INITIAL>"<"            return LT;
<INITIAL>"<="           return LE;

<INITIAL>[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.identifier = abc_string_create_identifier(yytext);
    return IDENTIFIER;
}

<INITIAL>([1-9][0-9]*)|"0" { 
    int int_val;
    sscanf(yytext, "%d", &int_val);
    yylval.int_val = int_val;
    return INT_LITERAL;
}

<INITIAL>[1-9]*[0-9]\.[0-9]+ {
    double double_val;
    sscanf(yytext, "%lf", &double_val);
    yylval.double_val = double_val;
    return DOUBLE_LITERAL;
}

<INITIAL>[ \t] ;
<INITIAL>\n { increment_line_number(); }
<INITIAL>. {
    /* error */
}
<INITIAL>#  BEGIN COMMENT_STATE
<INITIAL>\" {
    abc_string_start();
    BEGIN STRING_STATE;
}

<COMMENT_STATE>\n  { 
    increment_line_number();
    BEGIN INITIAL;
}

<STRING_STATE>\n {
    abc_string_add_char('\n');
    increment_line_number();
}
<STRING_STATE> \" {
    char *str = abc_string_end();
    yylval.str_val = str;
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\\"      abc_string_add_char('"');
<STRING_LITERAL_STATE>\\n       abc_string_add_char('\n');
<STRING_LITERAL_STATE>\\t       abc_string_add_char('\t');
<STRING_LITERAL_STATE>\\\\      abc_string_add_char('\\');
<STRING_LITERAL_STATE>.         abc_string_add_char(yytext[0]);
%%