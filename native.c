#include <stdio.h>
#include <string.h>
#include "abclang.h"

static void check_args_count(int arg_num, int expected_num, int line_num) {
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

static void check_args_type(ABC_Value *val, ABC_ValueType type, int line_num) {
    if (val->type != type) {
        abc_runtime_error(line_num, INCOMPATIBLE_VARIABLE_TYPE_ERR);
    }
}

ABC_Value abc_sys_print_proc(LocalEnvironment *env, 
                int arg_count, ABC_Value *args, int line_num) {
    ABC_Value result;
    ABC_Char *str;
    check_args_count(arg_count,1, line_num);

    result.type = ABC_NULL_VALUE;
    str = abc_value_to_string(&args[0]);
    abc_wcs_print(stdout, str);
    
    return result;
}

ABC_Value abc_sys_println_proc(LocalEnvironment *env, 
                int arg_count, ABC_Value *args, int line_num) {
    ABC_Value result;
    ABC_Char *str;

    check_args_count(arg_count,1, line_num);

    result.type = ABC_NULL_VALUE;
    str = abc_value_to_string(&args[0]);
    abc_wcs_println(stdout, str);
    
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

    filename = abc_wcstombs_alloc(args[0].u.object->u.str.str);
    mode = abc_wcstombs_alloc(args[1].u.object->u.str.str);

    fp = fopen(filename, mode);
    if (fp == NULL) {
        result.type = ABC_NULL_VALUE;
    } else {
        result.type = ABC_POINTER_VALUE;
        result.u.pointer.pointer = fp;
    }
    free(filename);
    free(mode);

    return result;
}

ABC_Value abc_sys_fclose_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num) {
    ABC_Value result;
    FILE *fp;

    check_args_count(arg_count,1, line_num);
    check_args_type(&args[0], ABC_POINTER_VALUE, line_num);

    result.type = ABC_NULL_VALUE;
    fp = args[0].u.pointer.pointer;
    fclose(fp);
    return result;
}

/*ABC_Value abc_sys_read_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num) {
    ABC_Value   result;
    FILE        *fp;
    char        *buf;
    size_t      read_size;
    size_t      arg_str_size;
    ABC_Char    *wcstr;


    check_args_count(arg_count, 3, line_num);
    check_args_type(&args[0], ABC_POINTER_VALUE, line_num);
    check_args_type(&args[1], ABC_STRING_VALUE, line_num);
    check_args_type(&args[2], ABC_INT_VALUE, line_num);

    result.type = ABC_INT_VALUE;
    fp = args[0].u.pointer.pointer;
    arg_str_size = abc_wcstombs_len(args[0].u.object->u.str.str);
    read_size = args[2].u.int_val;
    if (arg_str_size < read_size) {
        read_size = arg_str_size;
    }
    buf = (char *)MEM_malloc(sizeof(char) * read_size);
    read_size = fprintf(fp, buf, read_size);

    if (read_size > 0) {
        abc_mbsntowcs(buf, read_size, args[1].u.object->u.str.str);
        result.u.int_val = read_size;
    } else {
        result.u.int_val = 0;
    }

    free(buf);
    return result;
}

ABC_Value abc_sys_write_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num) {
    ABC_Value   result;
    FILE        *fp;
    char        *buf;
    size_t      write_size;
    size_t      arg_str_size;
    ABC_Char    *wcstr;


    check_args_count(arg_count, 3, line_num);
    check_args_type(&args[0], ABC_POINTER_VALUE, line_num);
    check_args_type(&args[1], ABC_STRING_VALUE, line_num);
    check_args_type(&args[2], ABC_INT_VALUE, line_num);

    result.type = ABC_INT_VALUE;
    fp = (FILE *)args[0].u.pointer;
    write_size = args[2].u.int_val;
    arg_str_size = abc_wcstombs_len(args[1].u.object->u.str.str);
    if (arg_str_size < write_size) {
        write_size = arg_str_size;
    }
    buf = abc_wcsntombs_alloc(args[1].u.object->u.str.str, write_size);
    write_size = fprintf(buf, write_size, fp);

    if (write_size > 0) {
        abc_mbsntowcs(buf, write_size, args[1].u.object->u.str.str);
        result.u.int_val = write_size;
    } else {
        result.u.int_val = 0;
    }

    free(buf);
    return result;
}*/

ABC_Value abc_sys_fgets_proc(LocalEnvironment *env, 
        int arg_count, ABC_Value *args, int line_num) {
    ABC_Value value;
    FILE *fp;
    char buf[LINE_BUF_SIZE];
    char *mb_buf = NULL;
    int ret_len = 0;
    ABC_Char *wc_str;

    check_args_count(arg_count, 1, line_num);
    check_args_type(&args[0], ABC_POINTER_VALUE, line_num);

    fp = args[0].u.pointer.pointer;

    while (fgets(buf, LINE_BUF_SIZE, fp)) {
        int new_len;
        new_len = ret_len + strlen(buf);
        mb_buf = MEM_realloc(mb_buf, new_len + 1);
        if (ret_len == 0) {
            strcpy(mb_buf, buf);
        } else {
            strcat(mb_buf, buf);
        }
        ret_len = new_len;
        if (mb_buf[ret_len-1] == '\n')
            break;
    }
    if (ret_len > 0) {
        wc_str = abc_mbstowcs_alloc(mb_buf);
        value.type = ABC_STRING_VALUE;
        value.u.object = abc_create_string(wc_str);
    } else {
        value.type = ABC_NULL_VALUE;
    }

    free(mb_buf);

    return value;
}

ABC_Value abc_sys_fputs_proc(LocalEnvironment *env,
                  int arg_count, ABC_Value *args, int line_num)
{
    ABC_Value value;
    FILE *fp;

    check_args_count(arg_count, 2, line_num);
    check_args_type(&args[0], ABC_STRING_VALUE, line_num);
    check_args_type(&args[1], ABC_POINTER_VALUE, line_num);

    value.type = ABC_INT_VALUE;
    fp = args[1].u.pointer.pointer;
    value.u.int_val = abc_wcs_print(fp, args[0].u.object->u.str.str);

    return value;
}

void abc_add_std_fp() {
    ABC_Value fp_value;

    fp_value.type = ABC_POINTER_VALUE;

    fp_value.u.pointer.pointer = stdin;
    abc_add_global_variable("STDIN", &fp_value);

    fp_value.u.pointer.pointer = stdout;
    abc_add_global_variable("STDOUT", &fp_value);

    fp_value.u.pointer.pointer = stderr;
    abc_add_global_variable("STDERR", &fp_value);
}