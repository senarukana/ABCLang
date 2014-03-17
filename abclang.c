#include <stdio.h>
#include <stdlib.h>
#include "abclang.h"
#include "y.tab.h"


static ABC_Interpreter *inter;

ABC_Interpreter *abc_get_interpreter() {
    return inter;
}

int abc_get_line_number() {
    return inter->line_num;
}


ABC_Interpreter *ABC_create_interpreter() {
    MEM_Storage *storage;

    storage = MEM_open_storage(0);
    inter = MEM_storage_malloc(storage,
                sizeof(struct ABC_Interpreter_tag));
    inter->interpreter_storage = storage;

    inter->heap.current_heap_size = 0;
    inter->heap.threshold_size = HEAP_THRESHOLDSIZE;
    inter->heap.front = NULL;

    inter->stack.pos = 0;
    inter->stack.alloc_size = STACK_ALLOC_SIZE;
    inter->stack.top = abc_excute_malloc(STACK_ALLOC_SIZE * sizeof(ABC_Value));
    return inter;
}

void ABC_compile(ABC_Interpreter *inter, FILE *fp) {
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "parse error\n");
        exit(1);
    }

}

void ABC_excute(ABC_Interpreter *inter) {
    
    abc_execute_statment_list(NULL, inter->statement_list);
}