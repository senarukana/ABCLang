#include "abclang.h"
#include "../memory.h"
#include <string.h>

#define STRING_BUF_SIZE (1024)

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
        abc_compile_error();
        return;
    }
    str_buf.buf[str_buf.pos++] = c;
    str_buf.buf[str_buf.pos] = '\0';
}

void abc_string_add_str(char *str) {
    int len;
    len = strlen(str);
    if (str_buf.pos + len >= STRING_BUF_SIZE) {
        abc_runtime_error();
    }
    strcpy(str_buf.buf[str_buf.pos], str);
    str_buf.pos += len + 1;
    str_buf.buf[str_buf.pos] = '\0';
}

char *abc_string_end() {
    char *str;

    str = abc_storage_malloc(str_buf.pos);
    strcpy(str, str_buf.buf);

    return str;
}

char *abc_string_create_identifier(char *str) {
    char *new_str;
    int len;

    len = strlen(str);
    new_str = abc_storage_malloc(len+1);
    strcpy(new_str, str);

    return new_str;
} 

void abc_vstr_clear(VString *v) {
    v->string = NULL;
}

static int abc_vstrlen(ABC_Char *str) {
    if (str == NULL) {
        return 0;
    }
    return abc_wcs_len(str);
}

void abc_vstr_append_string(VString *v, ABC_Char *str){
    int new_size;
    int old_len;

    old_len = abc_vstrlen(v->string);
    new_size = old_len + abc_wcs_len(str)  + 1;
    v->string = abc_excute_realloc(v->string, sizeof(ABC_Char) * new_size);
    abc_wcscpy(&v->string[old_len], str);
}

void
abc_vstr_append_character(VString *v, ABC_Char ch)
{
    int current_len;
    
    current_len = abc_vstrlen(v->string);
    v->string = abc_excute_realloc(v->string, sizeof(ABC_Char) *current_len + 2);
    v->string[current_len] = ch;
    v->string[current_len+1] = L'\0';
}

ABC_Char *abc_value_to_string(CRB_Value *value) {
    VString     vstr;
    char        buf[LINE_BUF_SIZE];
    ABC_Char    wc_buf[LINE_BUF_SIZE];
    int         i;

    crb_vstr_clear(&vstr);

    switch (value->type) {
    case ABC_BOOLEAN_VALUE:
        if (value->u.boolean_value) {
            abc_mbstowcs("true", wc_buf);
        } else {
            abs_mbstowcs("false", wc_buf);
        }
        crb_vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_INT_VALUE:
        sprintf(buf, "%d", value->u.int_value);
        abc_mbstowcs(buf, wc_buf);
        crb_vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_DOUBLE_VALUE:
        sprintf(buf, "%f", value->u.double_value);
        abc_mbstowcs(buf, wc_buf);
        abc_vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_STRING_VALUE:
        abc_vstr_append_string(&vstr, value->u.object->u.string.string);
        break;
    case ABC_NATIVE_POINTER_VALUE:
        sprintf(buf, "(%s:%p)",
                value->u.pointer.info->name,
                value->u.pointer.pointer);
        abc_mbstowcs(buf, wc_buf);
        abc_vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_NULL_VALUE:
        abc_mbstowcs("null", wc_buf);
        abc_vstr_append_string(&vstr, wc_buf);
        break;
    case ABC_ARRAY_VALUE:
        abc_mbstowcs("(", wc_buf);
        abc_vstr_append_string(&vstr, wc_buf);
        for (i = 0; i < value->u.object->u.array.size; i++) {
            ABC_Char *new_str;
            if (i > 0) {
                abc_mbstowcs(", ", wc_buf);
                abc_vstr_append_string(&vstr, wc_buf);
            }
            new_str = ABC_value_to_string(&value->u.object->u.array.array[i]);
            abc_vstr_append_string(&vstr, new_str);
            MEM_free(new_str);
        }
        abc_mbstowcs(")", wc_buf);
        abc_vstr_append_string(&vstr, wc_buf);
        break;
    default:
        abc_internal_error(-1, UNKNOWN_VALUE_TYPE_ERR);
    }

    return vstr.string;
}

