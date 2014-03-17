#include <wchar.h>
#include <stdio.h>
#include "abclang.h"

#define MB_LINE_BUF_SIZE (1024)

ABC_Char *abc_wcs_concate(ABC_Char *left, ABC_Char *right) {
    return wcscat(left, right);
}

bool *abc_wcs_cmp(ABC_Char *left, ABC_Char *right) {
    return wcscmp(left, right);
}

int abc_wcs_len(ABC_Char *str) {
    return wcslen(str);
}

ABC_Char *abc_wcscpy(ABC_Char *dest, ABC_Char *src) {
    return wcscpy(dest, src);
}

int abc_wcstombs_len(ABC_Char *src) {
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

int abc_wcstombs(ABC_Char *src, char *dest) {
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

char *abc_wcstombs_alloc(ABC_Char *src) {
    int src_idx, dest_idx;
    int status;
    int wclen;
    char *dest; 
    mbstate_t ps;

    wclen = abc_wcstombs_len(src);
    dest = abc_excute_malloc(wclen+1);

    for (src_idx = dest_idx = 0; src[src_idx] != L'\0'; ) {
        status = wcrtomb(&dest[dest_idx], src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }
    dest[dest_idx] = '\0';
    return dest;
}

int abc_mbstowcs_len(char *src) {
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

void abc_mbstowcs(char *src, ABC_Char *dest) {
    int src_idx, dest_idx,dest_len;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0') {
        status = mbrtowc(dest[dest_idx], &src[src_idx], MB_LINE_BUF_SIZE, &ps);
        dest_idx++;
        src_idx += status;
    }
    dest[dest_idx] = L'\0';
}

int abc_wcs_print(FILE *fp, ABC_Char *str) {
    char *buf;
    int len, result;

    len = abc_wcstombs_len(str);
    buf = abc_excute_malloc(len+1);
    abc_wcstombs(str, buf);
    fprintf(fp, "%s", buf);
    free(buf);
    
    return result; 
}

int abc_wcs_println(FILE *fp, ABC_Char *str) {
    int result;

    result = abc_wcs_print(fp, str);
    fprintf(fp,"\n");
    return result;
}  

