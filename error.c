#include <stdio.h>
#include "abclang.h"

#define ERROR_BUF_LINE_SIZE 1024

char *compile_error_msg[] = {
    {"dummy"},
    {"syntax error"},
    {"duplicate function definition"},
    {"dummy"}
}; 

char *runtime_error_msg[] = {
    "dummy",
    "VARAIBLE_NOT_FOUND_ERR",
    "VARIABLE_MULTIPLE_DEFINE_ERR",
    "UNCOMPARABLE_EXPRESSION_ERR",
    "FUNCTION_NOT_FOUND_ERR",
    "ARGUMENT_TOO_MANY_ERR",
    "ARGUMENT_TOO_FEW_ERR",
    "ASSIGN_EXPRESSION_ERR",
    "BAD_OPERATOR_FOR_STRING_ERR",
    "NULL_OPERATOR_ERR",
    "INVALID_COMPARE_ERR",
    "MINUS_OPERATOR_ERR",
    "INCR_OPERATOR_ERR",
    "DIV_ZERO_ERR",
    "NOT_BOOLEAN_TYPE_ERR",
    "dummy"
};

char *internal_err_msg[] = {
    "dummy",
    "UNKNOWN_EXPRESSION_TYPE_ERR",
    "UNKNOWN_STATEMENT_TYPE_ERR",
    "UNKNOWN_VALUE_TYPE_ERR",
    "dummy"
};

void abc_compile_error(ComipleErrorType type, char *msg) {
    fprintf(stderr, "line %3d, [%s] %s\n", abc_get_line_number(), msg, 
                compile_error_msg[type]);
    exit(1);
}

void abc_runtime_error(RuntimeErrorType type, int line_number) {
    fprintf(stderr,"line %3d, error:[%s]\n", line_number, 
                        runtime_error_msg[type]);
    exit(1);
}

void abc_internal_error(InternalErrorType type, int line_number) {
    fprintf(stderr,"internal error: %s\n", msg);
    exit(1);
}

int yyerror(char const *str) {
    char *near_token;

    if (yytext[0] == '\0') {
        near_token = "EOF";
    } else {
        near_token = yytext;
    }
    abc_compile_error(PARSE_ERR, near_token);
}