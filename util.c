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

int abc_value_compare(ABC_Value *a, ABC_Value *b) {
    if (a == NULL || b == NULL) {
        if (a == NULL && b== NULL) {
            return 0;
        } else {
            return 1;
        }
    }
    if (a->type != b->type) {
        return 1;
    }
    switch(a->type) {
    case ABC_INT_VALUE:
        return a->u.int_val - b->u.int_val;
        break;
    case ABC_DOUBLE_VALUE:
        return a->u.double_val - b->u.double_val;
    case ABC_BOOLEAN_VALUE:
        return a->u.bool_val - b->u.bool_val;
    case ABC_NULL_VALUE:
        return 0;
    case ABC_STRING_VALUE:
        return abc_wcs_cmp(a->u.object->u.str.str, b->u.object->u.str.str);
    default:
        abc_internal_error(-1, UNCOMPARABLE_TYPE);
    }
    /* make the compiler happy */
    return 0;
}
