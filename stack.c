#include "abclang.h"

void abc_stack_push_value(ABC_Value *value) {
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    if (inter->stack.pos == inter->stack.alloc_size) {
        inter->stack.alloc_size += STACK_ALLOC_SIZE;
        inter->stack.top = (ABC_Value*)MEM_realloc(inter->stack.top,
                        inter->stack.alloc_size * sizeof(ABC_Value));
    }
    inter->stack.top[inter->stack.pos++] = *value;
}

ABC_Value abc_stack_pop_value() {
    ABC_Value value;
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    value = inter->stack.top[--inter->stack.pos];

    return value;
}

void abc_stack_shrink(int num) {
    abc_get_interpreter()->stack.pos -= num;
}

ABC_Value *abc_stack_peek(int idx) {
    ABC_Interpreter *inter;
    inter = abc_get_interpreter();
    return &(inter->stack.top[inter->stack.pos-idx-1]);
}

