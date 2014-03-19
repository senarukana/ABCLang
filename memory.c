#include "abclang.h"

void *abc_storage_malloc(size_t size) {
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();

    return MEM_storage_malloc(inter->interpreter_storage, size);
}

void *abc_execute_malloc(size_t size) {
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    
    return MEM_storage_malloc(inter->execute_storage, size);
}