#include "abclang.h"

static FunctionDefinition *search_function(char *identifier) {
    ABC_Interpreter *inter;
    FunctionDefinition *fd;

    inter = abc_get_interpreter();
    fd = inter->function_list;
    while(fd->next != NULL) {
        if (memcmp(fd->identifier, identifier) == 0) {
            break;
        } 
    }
    return fd;
}

static LocalEnvironment *alloc_local_environment() {
    LocalEnvironment *env, *ep;
    ABC_Interpreter *inter;

    env = abc_execute_malloc(sizeof(LocalEnvironment));
    env->local_variable = NULL;
    inter = abc_get_interpreter();
    inter->next = inter->top_environment;
    inter->top_environment = env;
    return env;
}

static void dispose_local_environment() {
    ABC_Interpreter *inter;
    LocalEnvironment *env;
    VariableList *vp, *vtmp;

    inter = abc_get_interpreter();
    env = inter->top_environment;

    for (vp = env->local_variable; vp->next != NULL; vp = vp->next) {
        vtmp = vp->next;
        free(vp);
        vp = vtmp;
    }
    inter->top_environment = env->next;
    free(env);
}

static ABC_Value *search_variable(LocalEnvironment *env, char *identifier) {
    ABC_Interpreter *inter;
    VariableList *vp;

    // first search it in local_variable
    if (env != NULL) {
        vp = env->local_variable;
        while(vp->next != NULL) {
            if (memcmp(vp->identifier, identifier) == 0) {
                return vp;
            }
        }
    }
    // search it in global_variable
    inter = abc_get_interpreter();
    vp = inter->global_variable;
    while(vp->next != NULL) {
        if (memcmp(vp->identifier, identifier) == 0) {
            return vp;
        }
    }
    return NULL;
}

static void add_local_variable(LocalEnvironment *env, char *identifier, ABC_Value *value) {
    VariableList *vp, *new_variable;

    new_variable = abc_execute_malloc(sizeof(VariableList));
    new_variable->identifier = identifier;
    new_variable->value = *value;
    vp = env->local_variable;
    while(vp->next != NULL) {
        vp = vp->next;
    }
    new_variable->next = NULL;
    vp->next = new_variable;
}


static void eval_boolean_expression(ABC_Boolean bool_val) {
    ABC_Value val;
    val.type = ABC_BOOLEAN_VALUE;
    val.bool_val = bool_val;
    abc_stack_push_value(&val);
}

static void eval_int_expression(int int_val) {
    ABC_Value val;
    val.type = ABC_INT_VALUE;
    val.int_val = int_val;
    abc_stack_push_value(&val);
}

static void eval_double_expression(double double_val) {
    ABC_Value val;
    val.type = ABC_DOUBLE_VALUE;
    val.double_val = double_val;
    abc_stack_push_value(&val);
}

static void eval_string_expression(ABC_Char *string_value) {
    ABC_Value v;

    v.type = ABC_STRING_VALUE;
    v.u.object = abc_literal_to_object_string(string_value);
    abc_stack_push_value(&v);
}

static void eval_identifier_expression(LocalEnvironment *env, Expression *expr) {
    VariableList *vp;
    char *identifier;

    identifier = expr->u.identifier;

    vp = search_variable(env, identifier);
    if (vp != NULL) {
        abc_stack_push_value(&vp->value);
    } else {
        abc_runtime_error(expr->line_number, VARIABLE_NOT_FOUND_ERR);
    }
}

static void eval_binary_null_expression(ExpressionType type, 
            ABC_Value *left, ABC_Value *right, ABC_Value *result, int line_number) {
    result->type = ABC_Boolean;
    switch(type) {
    case EQUAL_EXPRESSION:
        result->u.bool_val = (left->type == ABC_NULL_VALUE && right->type == ABC_NULL_VALUE);
        break;
    case NOT_EQUAL_EXPRESSION:
        result->u.bool_val = !(left->type == ABC_NULL_VALUE && right->type == ABC_NULL_VALUE);
        break;
    default:
        abc_runtime_error(line_number, NULL_OPERATOR_ERR);
    }
}

static void eval_binary_int_expression(ExpressionType type, int left, int right, 
                ABC_Value *result, int line_number) {
    if (abc_is_math_operator(type)) {
        result->type = ABC_BOOLEAN_VALUE;
    } else {
        result->type = ABC_INT_VALUE;
    }
    switch(type) {
    case ADD_EXPRESSION:
        result->u.int_val = left + right;
        break;
    case SUB_EXPRESSION:
        result->u.int_val = left - right;
        break;
    case MUL_EXPRESSION:
        result->u.int_val = left * right;
        break;
    case DIV_EXPRESSION:
        if (right == 0) {
            abc_runtime_error(line_number, DIV_ZERO_ERR);
        }
        result->u.int_val = left / right;
        break;
    case MOD_EXPRESSION:
        result->u.int_val = left % right;
        break;
    case EQUAL_EXPRESSION:
        result->u.bool_val = left == right;
        break;
    case GT_EXPRESSION:
        result->u.bool_val = left > right;
        break;
    case GE_EXPRESSION:
        result->u.bool_val = left >= right;
        break;
    case LT_EXPRESSION:
        result->u.bool_val = left < right;
        break;
    case LE_EXPRESSION:
        result->u.bool_val = left <= right;
        break;
    default:
        abc_internal_error(line_number, UNKNOWN_EXPRESSION_TYPE_ERR);
    }
}

static void eval_binary_double_expression(ExpressionType type, 
            double left, double right, ABC_Value *result ,int line_number) {
    if (abc_is_math_operator(type)) {
        result->type = ABC_BOOLEAN_VALUE;
    } else {
        result->type = ABC_DOUBLE_VALUE;
    }
    switch(type) {
    case ADD_EXPRESSION:
        result->u.double_val = left + right;
        break;
    case SUB_EXPRESSION:
        result->u.double_val = left - right;
        break;
    case MUL_EXPRESSION:
        result->u.double_val = left * right;
        break;
    case DIV_EXPRESSION:
        if (right == 0) {
            abc_runtime_error(DIV_ZERO_ERR);
        }
        result->u.double_val = left / right;
        break;
    case MOD_EXPRESSION:
        result->u.double_val = left % right;
        break;
    case EQUAL_EXPRESSION:
        result->u.bool_val = left == right;
        break;
    case GT_EXPRESSION:
        result->u.bool_val = left > right;
        break;
    case GE_EXPRESSION:
        result->u.bool_val = left >= right;
        break;
    case LT_EXPRESSION:
        result->u.bool_val = left < right;
        break;
    case LE_EXPRESSION:
        result->u.bool_val = left <= right;
        break;
    default:
        abc_internal_error(line_number, UNKNOWN_EXPRESSION_TYPE_ERR);
    }
}

static void eval_string_compare(ExpressionType type, 
            ABC_String *left, ABC_String *right, ABC_String *result, int line_number) {
    result->type = ABC_BOOLEAN_VALUE;

    int cmp = abc_wcs_cmp(left, right);
    switch(type) {
    case EQUAL_EXPRESSION:
        result->u.bool_val = (cmp == 0);
        break;
    case NOT_EQUAL_EXPRESSION:
        result->.bool_val = (cmp != 0);
    case GT_EXPRESSION:
        result->u.bool_val = (cmp > 0);
        break;
    case GE_EXPRESSION:
        result->u.bool_val = (cmp >= 0);
        break;
    case LT_EXPRESSION:
        result->u.bool_val = (cmp < 0);
        break;
    case LE_EXPRESSION:
        result->u.bool_val = (cmp <= 0);
        break;
    default:
        abc_runtime_error(line_number, BAD_OPERATOR_FOR_STRING_ERR);
    }
}

static void concate_string(ABC_Value *left, ABC_Value *right, ABC_Value *result) {
    ABC_Char *right_str;
    ABC_Char *concate_str;
    ABC_Object *right_obj;
    int len;

    right_str = abc_value_to_string(right);
    right_obj = abc_create_string(right_str);

    len = abc_wcs_len(left->u.object->u.str.str) + 
            abc_wcs_len(right->u.object->u.str.str) + 1;
    concate_str = (ABC_Char *)abc_execute_malloc(sizeof(ABC_Char) * len);

    abc_wcs_concate(concate_str, left->u.object->str.str);
    abc_wcs_concate(concate_str, right_obj->u.str.str);
    result->type = ABC_STRING_VALUE;
    result->u.object = abc_create_string(concate_str);
}

static void eval_binary_expression(LocalEnvironment *env, 
        ExpressionType type, Expression *left, Expression *right) {
    ABC_Value *left_val, *right_val;
    ABC_Value result;

    eval_expression(env, left);
    eval_expression(env, right);
    left_val = &abc_stack_pop_value();
    right_val = &abc_stack_pop_value();

    if (left_val->type == ABC_INT_VALUE && right_val->type == ABC_INT_VALUE) {
        eval_binary_int_expression(type, 
                    left_val->u.int_val, right_val->u.int_val, 
                    &result, left->line_number);
    } else if (left_val->type == ABC_DOUBLE_VALUE && right_val->type == ABC_DOUBLE_VALUE) {
        eval_binary_double_expression(type, 
                    left_val->u.double_val, right_val->u.double_val, 
                    &result, left->line_number);
    } else if (left_val->type == ABC_INT_VALUE && right_val->type == ABC_DOUBLE_VALUE) {
        eval_binary_double_expression(type, 
                    (double)left->u.int_val, right_val->u.double_val, 
                    &result, left->line_number);
    } else if (left_val->type == ABC_DOUBLE_VALUE && right_val->type == ABC_INT_VALUE) {
        eval_binary_double_expression(type, 
                    left->u.double_val, (double)right_val->u.int_val, 
                    &result, left->line_number);
    } else if (left_val->type == ABC_STRING_VALUE && type == ADD_EXPRESSION) {
        concate_string(left_val, right_val, result);
    } else if (left_val->type == ABC_STRING_VALUE && right_val->type == ABC_STRING_VALUE) {
        eval_string_compare(type, 
                left_val->u.obj->str.str, right_val->u.obj->str.str, &result);
    } else if (left_val->type == ABC_NULL_VALUE || right_val->type == ABC_NULL_VALUE) {
        eval_binary_null_expression(left_val, right_val, 
                    &result, left->line_number);
    } else {
        abc_internal_error(left->line_number, UNKNOWN_EXPRESSION_TYPE_ERR);
    }
    abc_stack_push_value(&result);
}

static void eval_logical_expression(LocalEnvironment *env, 
            ExpressionType type, Expression *left, Expression *right, int line_number) {
    ABC_Value result;
    ABC_Value *left_val, *right_val;

    eval_expression(env, left);
    eval_expression(env, right);
    left_val = &abc_stack_pop_value();
    right_val = &abc_stack_pop_value();
    if (left_val->type != ABC_BOOLEAN_VALUE || right_val->type != ABC_BOOLEAN_VALUE) {
        abc_runtime_error(INVALID_COMPARE_ERR);
    }
    result.type = ABC_BOOLEAN_VALUE;
    switch(type) {
    case LOGICAL_AND_EXPRESSION:
        result.u.bool_val = (left_val->u.bool_val && right_val->u.bool_val);
    case LOGICAL_OR_EXPRESSION:
        result.u.bool_val = (left_val->u.bool_val || right_val->u.bool_val);
    default:
        abc_internal_error(line_number, UNKNOWN_EXPRESSION_TYPE_ERR);
    }

    abc_stack_push_value(&result);
}

static void eval_minus_expression(LocalEnvironment *env, Expression *expr) {
    ABC_Value result;
    ABC_Value *val;

    eval_expression(env, expr);
    val = &abc_stack_pop_value();
    switch(val->type) {
    case ABC_INT_VALUE:
        result->type = ABC_INT_VALUE;
        result->u.int_val = -(val->u.int_val);
        break;
    case ABC_DOUBLE_VALUE:
        result->type = ABC_DOUBLE_VALUE;
        result->u.double_val = -(val->u.double_val);
        break;
    default:
        abc_runtime_error(expr->line_number, MINUS_OPERATOR_ERR);
    }
    abc_stack_push_value(&result);
}

static void eval_incre_decre_expression(LocalEnvironment *env, ExpressionType type, Expression *expr) {
    ABC_Value result;
    ABC_Value *val;

    eval_expression(env, expr);
    val = &abc_stack_pop_value();
    switch(val->type) {
    case ABC_INT_VALUE:
        result->type = ABC_INT_VALUE;
        if (type == INCREMENT_EXPRESSION) {
            result->u.int_val++;
        } else {
            result->u.int_val--;
        }
        break;
    case ABC_DOUBLE_VALUE:
        result->type = ABC_DOUBLE_VALUE;
        if (type == INCREMENT_EXPRESSION) {
            result->u.double_val++;
        } else {
            result->u.double_val--;
        }
        break;
    default:
        abc_runtime_error(expr->line_number, INCR_OPERATOR_ERR);
    }
    abc_stack_push_value(&result);
}


static void eval_assign_expression(LocalEnvironment *env, Expression *left, Expression *right) {
    ABC_Value result;
    ABC_Value val;
    VariableList *vp;

    eval_expression(env, right);
    val = abc_stack_pop_value();
    if (left->type == IDENTIFIER_EXPRESSION) {
        vp = search_variable(env, left->u.identifier); 
        if (vp != NULL) {
            if (vp->type == val.type) {
                vp->value = val;
            } else {
                abc_runtime_error(UNCOMPARABLE_EXPRESSION_ERR);
            }
        } else {
            add_local_variable(env, left->u.identifier, &val);
        }
    } else if (left->type = INDEX_EXPRESSION) {
        printf("index expresion\n");
        return NULL;
    } else {
        abc_runtime_error(left->line_number ,ASSIGN_EXPRESSION_ERR);
    }
}

static void call_user_function(LocalEnvironment *env, LocalEnvironment *new_env,
            FunctionDefinition *fd, ArgumentList *arg_list, int line_number) {
    ABC_Value val;
    StatementResult result;
    ArgumentList *ap;
    ParameterList *pp;

    for (pp = fd->u.user_function.params, ap = arg_list; 
        pp->next != NULL && ap->next != NULL; 
        ap = ap->next, pp = pp->next) {
        eval_expression(new_env, ap);
        add_local_variable(new_env, pp->identifier, &abc_stack_pop_value); 
    }
    if (pp != NULL) {
        abc_runtime_error(line_number, ARGUMENT_TOO_FEW_ERR);
    }
    if (ap != NULL) {
        abc_runtime_error(line_number, ARGUMENT_TOO_MANY_ERR);
    }
    result = abc_execute_statement_list(new_env, fd->u.user_function.block->statement_list);
    if (result.type == RETURN_STATEMENT_RESULT) {
        val = result.value;
    } else {
        val.type = ABC_NULL_VALUE;
    }
    abc_stack_push_value(&val);
}

static void call_system_function(LocalEnvironment *env, LocalEnvironment *new_env, 
        FunctionDefinition *fd, ArgumentList *arg_list) {
    ABC_Value result;
    ABC_Value *args;
    ArgumentList *ap;
    int arg_count = 0;

    for (ap = arg_list; ap->next != NULL; ap = ap->next) {
        eval_expression(env, ap->expr);
        arg_count++;
    }
    args = abc_stack_peek(arg_count);
    result = fd->u.system_function.proc(new_env, args);
    abc_stack_shrink(arg_count);
    abc_stack_push_value(&result);
}

static void eval_function_call_expression(LocalEnvironment *env, 
        char *identifier, ArgumentList *arg_list, int line_number) {
    LocalEnvironment *new_env; 
    FunctionDefinition *fd;

    fd = search_function(identifier);
    if (fd == NULL) {
        abc_runtime_error(line_number, FUNCTION_NOT_FOUND_ERR);
    } 
    new_env = alloc_local_environment();

    if (fd->type == SYSTEM_FUNCTION) {
        call_system_function(env, new_env, fd, arg_list);
    } else {
        call_user_function(env, new_env, fd, arg_list);
    }
    dispose_local_environment();
}



static void eval_expression(LocalEnvironment *env, Expression *expr) {
    switch(expr->type) {
    case BOOLEAN_EXPRESSION:
        eval_boolean_expression(expr->u.boolean_val);
        break;
    case INT_EXPRESSION:
        eval_int_expression(expr->u.int_val);
        break;
    case DOUBLE_EXPRESSION:
        eval_double_expression(expr->u.double_val);
        break;
    case STRING_EXPRESSION:
        eval_string_expression(expr->u.string_val);
        break;
    case IDENTIFIER_EXPRESSION:
        eval_identifier_expression(expr->u.identifier_val, expr->line_number);
        break;
    case ASSIGN_EXPRESSION:
        eval_assign_expression(env, 
            expr->u.assign_expr.left, expr->u.assign_expr.right
            expr->line_number);
        break;
    case LOGICAL_AND_EXPRESSION:
    case LOGICAL_OR_EXPRESSION:
        eval_logical_expression(env, expr->type, 
                expr->u.binary_expr.left, expr->u.binary_expr.right, 
                expr->line_number);
        break;
    case EQUAL_EXPRESSION:
    case NOT_EQUAL_EXPRESSION:
    case GT_EXPRESSION:
    case GE_EXPRESSION:
    case LT_EXPRESSION:
    case LE_EXPRESSION:
    case ADD_EXPRESSION:
    case SUB_EXPRESSION:
    case MUL_EXPRESSION:
    case DIV_EXPRESSION:
        eval_binary_expression(env, expr->type,
                expr->u.binary_expr.left, expr->u.binary_expr.right);
        break;
    case MINUS_EXPRESSION:
        eval_minus_expression(env, expr->singular_expr);
        break;
    case INCREMENT_EXPRESSION:
    case DECREMENT_EXPRESSION:
        eval_incre_decre_expression(env, expr->singular_expr);
        break;
    // case METHOD_CALL_EXPRESSION:
        // eval_method_call_expression(env, expr);
    case FUNCTION_CALL_EXPRESSION:
        eval_function_call_expression(env, 
            expr->u.func_expr.identifier, 
            expr->u.func_expr.args,
            expr->line_number);
        break;
    default:
        abc_internal_error(expr->line_number, UNKNOWN_EXPRESSION_TYPE_ERR);
    }  
}

ABC_Value abc_eval_expression(LocalEnvironment *env, Expression *expr) {
    eval_expression(env, expr);
    return abc_stack_pop_value();
}