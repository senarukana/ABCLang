#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abclang.h"
#include "y.tab.h"


static ABC_Interpreter *inter;

ABC_Interpreter *abc_get_interpreter() {
    return inter;
}

int abc_get_line_number() {
    return inter->line_num;
}

static void add_system_proc(char *identifier, ABC_SystemFuncPorc *proc) {
    FunctionDefinition *fd;

    fd = abc_storage_malloc(sizeof(FunctionDefinition));
    fd->type = SYSTEM_FUNCTION;
    fd->identifier = abc_storage_malloc(strlen(identifier)+1);
    strcpy(fd->identifier, identifier);
    fd->u.system_function.proc = proc;
    fd->next = inter->func_list;
    inter->func_list = fd;
}

static void add_system_procs() {
    add_system_proc("print", abc_sys_print_proc);
    add_system_proc("println", abc_sys_println_proc);
    add_system_proc("fopen", abc_sys_fopen_proc);
    add_system_proc("fclose", abc_sys_fclose_proc);
/*    add_system_proc("fread", abc_sys_fread_proc);
    add_system_proc("fwrite", abc_sys_fwrite_proc);*/
    add_system_proc("fgets", abc_sys_fgets_proc);
    add_system_proc("fputs", abc_sys_fputs_proc);
}


ABC_Interpreter *ABC_create_interpreter() {
    MEM_Storage *interpret_storage;

    interpret_storage = MEM_open_storage(0);
    inter = MEM_storage_malloc(interpret_storage,
                sizeof(struct ABC_Interpreter_tag));
    inter->interpreter_storage = interpret_storage;
    inter->global_variable = NULL;
    inter->statement_list = NULL;
    inter->func_list = NULL;

    inter->heap.current_heap_size = 0;
    inter->heap.threshold_size = HEAP_THRESHOLDSIZE;
    inter->heap.front = NULL;

    inter->stack.pos = 0;
    inter->stack.alloc_size = STACK_ALLOC_SIZE;
    inter->stack.top = MEM_malloc(STACK_ALLOC_SIZE * sizeof(ABC_Value));
    add_system_procs();
    return inter;
}

void ABC_compile(ABC_Interpreter *inter, FILE *fp) {
    extern int yyparse(void);
    extern FILE *yyin;
    fprintf(stderr, "begin compile\n");
    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "parse error\n");
        exit(1);
    }
    fprintf(stderr, "end compile\n");
}

void ABC_execute(ABC_Interpreter *inter) {
    inter->execute_storage = MEM_open_storage(0);
    abc_add_std_fp();
    fprintf(stderr, "begin execute\n");
    abc_execute_statement_list(NULL, inter->statement_list);
}
