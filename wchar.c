#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abclang.h"

#define MB_LINE_BUF_SIZE (1024)

ABC_Char *abc_wcs_concate(ABC_Char *left, ABC_Char *right) {
    return wcscat(left, right);
}

int abc_wcs_cmp(ABC_Char *left, ABC_Char *right) {
    return wcscmp(left, right);
}

int abc_wcs_len(ABC_Char *str) {
    return wcslen(str);
}

ABC_Char *abc_wcs_cpy(ABC_Char *dest, ABC_Char *src) {
    return wcscpy(dest, src);
}

int abc_wcstombs_len(const ABC_Char *src) {
    int src_idx, dest_idx;
    int status;
    char dummy[MB_LINE_BUF_SIZE];
    mbstate_t ps;

    for (src_idx = dest_idx = 0; src[src_idx] != L'\0'; ) {
        status = wcrtomb(dummy, src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }

    return dest_idx;
}

int abc_wcstombs(const ABC_Char *src, char *dest) {
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    for (src_idx = dest_idx = 0; src[src_idx] != L'\0'; ) {
        status = wcrtomb(&dest[dest_idx], src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }
    dest[dest_idx] = '\0';
    return 1;
}

char *abc_wcstombs_alloc(const ABC_Char *src) {
    int src_idx, dest_idx;
    int status;
    int wclen;
    char *dest; 
    mbstate_t ps;

    wclen = abc_wcstombs_len(src);
    dest = MEM_malloc(wclen+1);

    for (src_idx = dest_idx = 0; src[src_idx] != L'\0'; ) {
        status = wcrtomb(&dest[dest_idx], src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }
    dest[dest_idx] = '\0';
    return dest;
}

char *abc_wcsntombs_alloc(const ABC_Char *src, int len) {
    int src_idx, dest_idx;
    int status;
    int wclen;
    char *dest; 
    mbstate_t ps;

    wclen = abc_wcstombs_len(src);
    dest = MEM_malloc(wclen+1);

    for (src_idx = dest_idx = 0; src[src_idx] != L'\0' && dest_idx < len; ) {
        status = wcrtomb(&dest[dest_idx], src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }
    dest[len+1] = '\0';
    return dest;
}

int abc_mbstowcs_len(const char *src) {
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0';) {
        status = mbrtowc(NULL, &src[src_idx], MB_LINE_BUF_SIZE, &ps);
        if (status < 0) {
            return status;
        }
        dest_idx++;
        src_idx += status;
    }

    return dest_idx;
}

void abc_mbstowcs(const char *src, ABC_Char *dest) {
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0';) {
        status = mbrtowc(&dest[dest_idx], &src[src_idx], MB_LINE_BUF_SIZE, &ps);
        dest_idx++;
        src_idx += status;
    }
    dest[dest_idx] = L'\0';
}

void abc_mbsntowcs(const char *src, int len, ABC_Char *dest) {
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src_idx < len;) {
        status = mbrtowc(&dest[dest_idx], &src[src_idx], MB_LINE_BUF_SIZE, &ps);
        dest_idx++;
        src_idx += status;
    }
    dest[dest_idx] = L'\0';
}

ABC_Char *abc_mbstowcs_alloc(const char *src) {
    int len;
    ABC_Char *ret;

    len = abc_mbstowcs_len(src);
    if (len < 0) {
        abc_runtime_error(-1, BAD_CHARACTER_ERR);
    }
    ret = MEM_malloc(sizeof(ABC_Char) * (len+1));
    abc_mbstowcs(src, ret);

    return ret;
}

int abc_wcs_print(FILE *fp, ABC_Char *str) {
    char *buf;
    int len, result;

    len = abc_wcstombs_len(str);
    buf = MEM_malloc(len+1);
    abc_wcstombs(str, buf);
    result = fprintf(fp, "%s", buf);
    free(buf);
    return result; 
}

int abc_wcs_println(FILE *fp, ABC_Char *str) {
    int result;

    result = abc_wcs_print(fp, str);
    fprintf(fp,"\n");
    return result;
}  

