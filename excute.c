#include "abclang.h"

static StatementResult execute_elseif(LocalEnvironment *env, ElseIfList *else_if_list,
        ABC_Boolean *executed) {
    StatementResult result;
    Expression *expr;
    ElseIfList *ep;
    result.type = NORMAL_STATEMENT_RESULT;

    for (ep = else_if_list; ep; ep = ep->list) {
        val = abc_eval_expression(ep->cond);
        if (val.type != ABC_BOOLEAN_VALUE) {
            abc_runtime_error(ep->cond->line_number, NOT_BOOLEAN_TYPE_ERR);
        } else {
            if (val.u.bool_val) {
                *executed = ABC_True;
                return abc_execute_statment_list(env, ep->block->statement_list);
            }
        }
    }
    return result;
}

static StatementResult execute_if_statement(LocalEnvironment *env, IfStatement *stmt) {
    StatementResult result;
    Expression *expr;
    ABC_Value val;
    ABC_Boolean excuted;

    executed = ABC_False;
    result.type = NORMAL_STATEMENT_RESULT;
    val = abc_eval_expression(stmt->if_cond);
    if (val.type != ABC_BOOLEAN_VALUE) {
        abc_runtime_error(stmt->line_number, NOT_BOOLEAN_TYPE_ERR);
    }
    if (val.u.bool_val) {
        return abc_execute_statment_list(env, stmt->if_block->statement_list);
    } else {
        if (stmt->else_if) {
            result = execute_elseif(env, stmt->else_if, &executed);
            if (executed) {
                return result;
            }
        }
        if (stmt->else_block) {
            return abc_execute_statment_list(env, stmt->else_block->statement_list);
        }
    }
    return result;
}

static StatementResult execute_return_statement(LocalEnvironment *env, ReturnStatement *stmt) {
    StatementResult result;

    result.type = RETURN_STATEMENT_RESULT;
    if (stmt.value) {
        result.value = abc_eval_expression(env, stmt->u.epxr);
    } else {
        result.value.type = ABC_NULL_VALUE;
    }

    return result;
}

static StatementResult execute_continue_statement() {
    StatementResult result;

    result.type = CONTINUE_STATEMENT_RESULT;

    return reuslt;
}

static StatementResult execute_break_statement() {
    StatementResult result;

    result.type = BREAK_STATEMENT_RESULT;

    return result;
}

static StatementResult execute_for_statement(LocalEnvironment *env, ForStatement *stmt) {
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;

    return result;
}

static StatementResult execute_while_statement(LocalEnvironment *env, WhileStatement *stmt) {
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;

    return result;
}


static StatementResult excute_statement(LocalEnvironment *env, Statement *stmt) {
    StatementResult result;

    switch(stmt->type) {
    case IF_STATEMENT:
        result = execute_if_statement(env, &stmt->u.if_stat);
        break;
    case FOR_STATEMENT:
        result = execute_for_statement(env, &stmt->u.for_stat);
        break;
    case WHILE_STATEMENT:
        result = execute_while_statement(env, &stmt->u.while_stat);
        break;
    case RETURN_STATEMENT:
        result = execute_return_statement();
        break;
    case BREAK_STATEMENT:
        result = execute_break_statement();
        break;
    case CONTINUE_STATEMENT:
        result = execute_continue_statement();
        break;
    default:
        abc_internal_error(stmt->line_number, UNKNOWN_STATEMENT_TYPE_ERR);
    }
    return result;
}

void abc_execute_statment_list(LocalEnvironment *env, StatementList *list) {
    StatementList *pos;
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;
    pos = list;
    while(pos->next != NULL) {
        result = excute_statement(env, pos->statement);
        if (result.type != NORMAL_STATEMENT_RESULT) {
            break;
        }
    }
    return result;
}
