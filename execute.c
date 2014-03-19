#include "abclang.h"

/*
 * Functions to parse statements.
 *
 */

 MessageFormat statement_type_str[] = {
    {"dummy"},
    {"EXPRESSION_STATEMENT"},
    {"IF_STATEMENT"},
    {"FOR_STATEMENT"},
    {"WHILE_STATEMENT"},
    {"RETURN_STATEMENT"},
    {"BREAK_STATEMENT"},
    {"CONTINUE_STATEMENT"},
    {"dummy"},
};

static StatementResult execute_expression_statement(LocalEnvironment *env, Expression *expr) {
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;
    abc_eval_expression(env, expr);

    return result;
}

static StatementResult execute_elseif(LocalEnvironment *env, ElseIfList *else_if_list,
        ABC_Bool *executed) {
    StatementResult result;
    ABC_Value val;
    ElseIfList *ep;
    result.type = NORMAL_STATEMENT_RESULT;

    for (ep = else_if_list; ep; ep = ep->next) {
        val = abc_eval_expression(env, ep->cond);
        if (val.type != ABC_BOOLEAN_VALUE) {
            abc_runtime_error(ep->cond->line_num, NOT_BOOLEAN_TYPE_ERR);
        } else {
            if (val.u.bool_val) {
                *executed = ABC_True;
                return abc_execute_statement_list(env, ep->block->statement_list);
            }
        }
    }
    return result;
}

static StatementResult execute_if_statement(LocalEnvironment *env, IfStatement *stmt, int line_num) {
    StatementResult result;
    ABC_Value val;
    ABC_Bool executed;

    executed = ABC_False;
    result.type = NORMAL_STATEMENT_RESULT;
    val = abc_eval_expression(env, stmt->if_cond);
    if (val.type != ABC_BOOLEAN_VALUE) {
        abc_runtime_error(line_num, NOT_BOOLEAN_TYPE_ERR);
    }
    if (val.u.bool_val) {
        return abc_execute_statement_list(env, stmt->if_block->statement_list);
    } else {
        if (stmt->elseif) {
            result = execute_elseif(env, stmt->elseif, &executed);
            if (executed) {
                return result;
            }
        }
        if (stmt->else_block) {
            return abc_execute_statement_list(env, stmt->else_block->statement_list);
        }
    }
    return result;
}

static StatementResult execute_for_statement(LocalEnvironment *env, ForStatement *stmt, int line_num) {
    StatementResult result;
    ABC_Value cond;

    result.type = NORMAL_STATEMENT_RESULT;
    if (stmt->init) {
        abc_eval_expression(env,stmt->init);
    }
    for (;;) {
        if (stmt->cond != NULL) {
            cond = abc_eval_expression(env, stmt->cond);
            if (cond.type != ABC_BOOLEAN_VALUE) {
                abc_runtime_error(line_num, UNCOMPARABLE_EXPRESSION_ERR);
            }
            if (!cond.u.bool_val) {
                goto FOR_END;
            }
        }

        result = abc_execute_statement_list(env, stmt->block->statement_list);
        switch(result.type) {
        case RETURN_STATEMENT_RESULT:
            goto FOR_END;
            break;
        case BREAK_STATEMENT_RESULT:
            result.type = NORMAL_STATEMENT_RESULT;
            goto FOR_END;
            break;
        default:    /* CONTINUE_STATEMENT, NORMAL_STATEMENT */
            break;
        }
        if (stmt->post) {
            abc_eval_expression(env, stmt->post);
        }
    }
FOR_END:
    return result;
}

static StatementResult execute_while_statement(LocalEnvironment *env, WhileStatement *stmt, int line_num) {
    StatementResult result;
    ABC_Value cond;

    result.type = NORMAL_STATEMENT_RESULT;
    for (;;) {
        if (stmt->cond != NULL) {
            cond = abc_eval_expression(env, stmt->cond);
            if (cond.type != ABC_BOOLEAN_VALUE) {
                abc_runtime_error(line_num, UNCOMPARABLE_EXPRESSION_ERR);
            }
            if (!cond.u.bool_val) {
                goto WHILE_END;
            }
        }
        if (stmt->block == NULL) {
            abc_runtime_error(line_num, INFINITE_WHILE_LOOP_ERR);
        }
        result = abc_execute_statement_list(env, stmt->block->statement_list);
        switch(result.type) {
        case RETURN_STATEMENT_RESULT:
            goto WHILE_END;
            break;
        case BREAK_STATEMENT_RESULT:
            result.type = NORMAL_STATEMENT_RESULT;
            goto WHILE_END;
            break;
        default:    /* CONTINUE_STATEMENT, NORMAL_STATEMENT */
            break;
        }
    }

WHILE_END:
    return result;
}

static StatementResult execute_return_statement(LocalEnvironment *env, ReturnStatement *stmt) {
    StatementResult result;

    result.type = RETURN_STATEMENT_RESULT;
    if (stmt->expr) {
        result.value = abc_eval_expression(env, stmt->expr);
    } else {
        result.value.type = ABC_NULL_VALUE;
    }

    return result;
}

static StatementResult execute_continue_statement() {
    StatementResult result;

    result.type = CONTINUE_STATEMENT_RESULT;

    return result;
}

static StatementResult execute_break_statement() {
    StatementResult result;

    result.type = BREAK_STATEMENT_RESULT;

    return result;
}


static StatementResult excute_statement(LocalEnvironment *env, Statement *stmt) {
    StatementResult result;
    fprintf(stderr, "statement type:%s\n", statement_type_str[stmt->type].format);
    switch(stmt->type) {
    case EXPRESSION_STATEMENT:
        result = execute_expression_statement(env, stmt->u.expr_stat);
        break;
    case IF_STATEMENT:
        result = execute_if_statement(env, &stmt->u.if_stat, stmt->line_num);
        break;
    case FOR_STATEMENT:
        result = execute_for_statement(env, &stmt->u.for_stat, stmt->line_num);
        break;
    case WHILE_STATEMENT:
        result = execute_while_statement(env, &stmt->u.while_stat, stmt->line_num);
        break;
    case RETURN_STATEMENT:
        result = execute_return_statement(env, &stmt->u.return_stat);
        break;
    case BREAK_STATEMENT:
        result = execute_break_statement();
        break;
    case CONTINUE_STATEMENT:
        result = execute_continue_statement();
        break;
    default:
        abc_internal_error(stmt->line_num, UNKNOWN_STATEMENT_TYPE_ERR);
    }
    return result;
}

StatementResult abc_execute_statement_list(LocalEnvironment *env, StatementList *list) {
    StatementList *pos;
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;
    pos = list;
    while(pos != NULL) {
        fprintf(stderr, "execute...\n");
        result = excute_statement(env, pos->statement);
        if (result.type != NORMAL_STATEMENT_RESULT) {
            break;
        }
        pos = pos->next;
    }
    return result;
}
