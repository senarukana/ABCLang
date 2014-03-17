#include <stdio.h>
#include "abclang.h"

static void check_args(int arg_num, int expected_num, int line_num) {
    if (arg_num > expected_num) {
        abc_runtime_error(line_num, ARGUMENT_TOO_MANY_ERR);
    } else if (arg_num < expected_num){
        abc_runtime_error(line_num, ARGUMENT_TOO_FEW_ERR);
    }
}

static void check_args_range(int arg_num, int minimum, int maximum, int line_num) {
    if (arg_num > maximum) {
        abc_runtime_error(line_num, ARGUMENT_TOO_MANY_ERR);
    } else if (arg_num < minimum){
        abc_runtime_error(line_num, ARGUMENT_TOO_FEW_ERR);
    }
}

ABC_Value abc_sys_print_proc(LocalEnvironment *env, 
                int arg_count, ABC_Value *args, int line_num) {
    ABC_Value result;
    ABC_Char *str;

    check_args(arg_count,1, line_num);

    result.type = ABC_NULL;
    str = abc_value_to_string(&args[0]);
    abc_wcs_print(stdout, str);
    
    free(str);
    return result;
}

ABC_Value abc_sys_fopen_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num) {
    ABC_Value result;
    char *filename, *mode;
    FILE *fp;

    check_args_range(arg_count, 1, 2, line_num);

    if (args[0].type != ABC_STRING_VALUE) {
        abc_runtime_error(line_num, UNCOMPARABLE_EXPRESSION_ERR);
    } 
    if (arg_count == 2 && args[1]. type != ABC_STRING_VALUE) {
        abc_runtime_error(line_num, UNCOMPARABLE_EXPRESSION_ERR);
    } 

    filename = abc_wcstombs_alloc(args[0].u.object.str.str);
    mode = abc_wcstombs_alloc(args[1].u.object.str.str);

    fp = fopen(filename, mode);
    if (fp == NULL) {
        result.type = ABC_NULL_VALUE;
    } else {
        result.type = ABC_NATIVE_POINTER;
        result.u.pointer.pointer = fp;
    }
    free(filename);
    free(mode);

    return result;
}