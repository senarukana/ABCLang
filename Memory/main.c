#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main() {
    MEM_Storage *s = MEM_open_storage(0);
    int *a = (int *)MEM_storage_malloc(s, sizeof(int) * 100);
    printf("%d\n", s->page_num);
    int *b = (int *)MEM_storage_malloc(s, sizeof(int) * 250);
    printf("%d\n", s->page_num);
}