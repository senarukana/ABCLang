#include "abclang.h"
#include <string.h>

void abc_add_local_variable(LocalEnvironment *env, char *identifier, ABC_Value *value) {
    VariableList *new_variable;

    new_variable = MEM_malloc(sizeof(VariableList));
    new_variable->identifier = identifier;
    new_variable->value = *value;
    new_variable->next = env->local_variable;
    env->local_variable = new_variable;
}

void abc_add_global_variable(char *identifier, ABC_Value *value) {
    VariableList *new_variable;
    ABC_Interpreter *inter;

    fprintf(stderr, "add global_variable %s\n", identifier);

    inter = abc_get_interpreter();
    new_variable = abc_execute_malloc(sizeof(VariableList));
    new_variable->identifier = abc_execute_malloc(strlen(identifier)+1);
    strcpy(new_variable->identifier, identifier);
    new_variable->value = *value;
    new_variable->next = inter->global_variable;
    inter->global_variable = new_variable;
}
