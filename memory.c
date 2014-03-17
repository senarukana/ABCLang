#include "../memory.h"

void *abc_storage_malloc(size_t size) {
    void *p;
    ABC_Intepreter *inter;

    inter = abc_get_interpreter();
    p = MEM_storage_malloc(inter->interpreter_storage, size);

    return p;
}

void *abc_excute_malloc(size_t size) {
    return MEM_malloc(size);
}

void *abc_execute_realloc(void *ptr, size_t size) {
    return MEM_realloc(ptr, size);
}