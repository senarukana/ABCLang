#include "abclang.h"
#include <string.h>

#define STRING_BUF_SIZE (1024)

typedef struct {
    ABC_Char *string;
} VString;

typedef struct{
    int pos;
    char buf[STRING_BUF_SIZE];
} StrBuffer;

StrBuffer str_buf;

void abc_string_start() {
    str_buf.pos = 0;
    str_buf.buf[0] = '\0';
}

void abc_string_add_char(char c) {
    if (str_buf.pos >= STRING_BUF_SIZE) {
        abc_compile_error(STATEMENT_TOO_LONG_ERR, str_buf.buf);
        return;
    }
    str_buf.buf[str_buf.pos++] = c;
    str_buf.buf[str_buf.pos] = '\0';
}

ABC_Char *abc_string_end() {
    ABC_Char *new_str;
    int  new_str_len;

    abc_string_add_char('\0');
    new_str_len = abc_mbstowcs_len(str_buf.buf);
    if (new_str_len < 0) {
        abc_compile_error(INVALID_CHARACTER_ERR, str_buf.buf);
    }
    new_str = abc_storage_malloc(new_str_len * sizeof(ABC_Char));
    abc_mbstowcs(str_buf.buf, new_str);

    return new_str;
}

char *abc_string_create_identifier(char *str) {
    char *new_str;
    int len;

    len = strlen(str);
    new_str = abc_storage_malloc(len+1);
    strcpy(new_str, str);

    return new_str;
} 

static void vstr_clear(VString *v) {
    v->string = NULL;
}

static int vstr_len(ABC_Char *str) {
    if (str == NULL) {
        return 0;
    }
    return abc_wcs_len(str);
}

static void vstr_append_string(VString *v, ABC_Char *str){
    int new_size;
    int old_len;

    old_len = vstr_len(v->string);
    new_size = old_len + abc_wcs_len(str)  + 1;
    v->string = MEM_realloc(v->string, sizeof(ABC_Char) * new_size);
    abc_wcs_cpy(&v->string[old_len], str);
}

static void vstr_append_character(VString *v, ABC_Char ch) {
    int current_len;
    
    current_len = vstr_len(v->string);
    v->string = MEM_realloc(v->string, sizeof(ABC_Char) *current_len + 2);
    v->string[current_len] = ch;
    v->string[current_len+1] = L'\0';
}

ABC_Char *abc_value_to_string(ABC_Value *value) {
    VString     vstr;
    char        buf[LINE_BUF_SIZE];
    ABC_Char    wc_buf[LINE_BUF_SIZE];
    int         i;

    vstr_clear(&vstr);

    switch (value->type) {
    case ABC_BOOLEAN_VALUE:
        if (value->u.bool_val) {
            abc_mbstowcs("true", wc_buf);
        } else {
            abc_mbstowcs("false", wc_buf);
        }
        vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_INT_VALUE:
        sprintf(buf, "%d", value->u.int_val);
        abc_mbstowcs(buf, wc_buf);
        vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_DOUBLE_VALUE:
        sprintf(buf, "%f", value->u.double_val);
        abc_mbstowcs(buf, wc_buf);
        vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_STRING_VALUE:
        vstr_append_string(&vstr, value->u.object->u.str.str);
        break;
    case ABC_POINTER_VALUE:
        sprintf(buf, "(%s:%p)",
                value->u.pointer.name,
                value->u.pointer.pointer);
        abc_mbstowcs(buf, wc_buf);
        vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_NULL_VALUE:
        abc_mbstowcs("null", wc_buf);
        vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_ARRAY_VALUE:
        abc_mbstowcs("(", wc_buf);
        vstr_append_string(&vstr, wc_buf);
        for (i = 0; i < value->u.object->u.array.size; i++) {
            ABC_Char *new_str;
            if (i > 0) {
                abc_mbstowcs(", ", wc_buf);
                vstr_append_string(&vstr, wc_buf);
            }
            new_str = abc_value_to_string(&value->u.object->u.array.array[i]);
            vstr_append_string(&vstr, new_str);
            free(new_str);
        }
        abc_mbstowcs(")", wc_buf);
        vstr_append_string(&vstr, wc_buf);
        break;
    default:
        abc_internal_error(-1, UNKNOWN_VALUE_TYPE_ERR);
    }

    return vstr.string;
}

