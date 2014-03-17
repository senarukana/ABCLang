#ifndef ABC_PRIVATE__
#define ABC_PRIVATE__
#include <wchar.h>

#define HEAP_ALLOC_SIZE     (1024 * 32)
#define STACK_ALLOC_SIZE    (1024 * 32)
#define LINE_BUF_SIZE       (256)
#define HEAP_THRESHOLDSIZE  (1024 * 256)

/* Variable Type */
typedef wchar_t ABC_Char;

typedef enum {
    ABC_False,
    ABC_True
} ABC_Bool;

typedef struct {
    char    *name;
    void    *pointer;
} ABC_Pointer; 

typedef enum {
    ABC_INT_VALUE = 1,
    ABC_DOUBLE_VALUE,
    ABC_BOOLEAN_VALUE,
    ABC_NULL_VALUE,
    ABC_POINTER_VALUE,
    ABC_STRING_VALUE,
    ABC_ARRAY_VALUE,
    ABC_MAP_VALUE
} ABC_ValueType;

typedef enum {
    ARRAY_OBJECT = 1,
    STRING_OBJECT,
    MAP_OBJECT
} ObjectType;

typedef struct ABC_String {
    int         is_literal;
    ABC_Char    *str;
};

typedef struct ABC_Array {
    int         len;
    int         alloc_size;
    ABC_Value   *array;
};

typedef struct ABC_Object_tag {
    ABC_ValueType   type;
    int             mark:1;
    union {
        ABC_String  str;
        ABC_Array   array;
    } u;
    struct ABC_Object_tag *prev;
    struct ABC_Object_tag *next;
} ABC_Object;

typedef struct ABC_Value {
    ABC_ValueType type;
    union {
        int         int_val;
        double      double_val;
        ABC_Bool    bool_val;
        ABC_Pointer *pointer;
        ABC_Object  *object;
    }u;
};

/* Error */
typedef enum {
    PARSE_ERR = 1,
    FUNCTION_MULTIPLE_DEFINE_ERR,
} CompileErrorType;

typedef enum {
    VARAIBLE_NOT_FOUND_ERR = 1,
    VARIABLE_MULTIPLE_DEFINE_ERR,
    UNCOMPARABLE_EXPRESSION_ERR,
    FUNCTION_NOT_FOUND_ERR,
    ARGUMENT_TOO_MANY_ERR,
    ARGUMENT_TOO_FEW_ERR,
    ASSIGN_EXPRESSION_ERR,
    BAD_OPERATOR_FOR_STRING_ERR,
    NULL_OPERATOR_ERR,
    INVALID_COMPARE_ERR,
    MINUS_OPERATOR_ERR,
    INCR_OPERATOR_ERR,
    DIV_ZERO_ERR,
    NOT_BOOLEAN_TYPE_ERR
} RuntimeErrorType;

typedef enum {
    UNKNOWN_EXPRESSION_TYPE_ERR = 1,
    UNKNOWN_STATEMENT_TYPE_ERR,
    UNKNOWN_VALUE_TYPE_ERR,
} InternalErrorType;

/* Expression Definition */
typedef struct Expression_tag Expression;
typedef struct Statement_tag  Statement;
typedef struct LocalEnvironment_tag LocalEnvironment;
typedef struct Block_tag Block;
typedef struct ABC_interpreter_tag ABC_interpreter;

typedef ABC_Value ABC_SystemFuncPorc(LocalEnvironment *env, int arg_count, ABC_Value *args, int line_num); 

typedef enum {
    INT_EXPRESSION = 1,
    DOUBLE_EXPRESSION,
    STRING_EXPRESSION,
    BOOLEAN_EXPRESSION,
    NULL_EXPRESSION,
    ARRAY_EXPRESSION,
    IDENTIFIER_EXPRESSION ,
    ASSIGN_EXPRESSION,
    LOGICAL_AND_EXPRESSION,
    LOGICAL_OR_EXPRESSION,
    EQUAL_EXPRESSION,
    NOT_EQUAL_EXPRESSION,
    GT_EXPRESSION,
    GE_EXPRESSION,
    LT_EXPRESSION,
    LE_EXPRESSION,
    ADD_EXPRESSION,
    SUB_EXPRESSION,
    MUL_EXPRESSION,
    DIV_EXPRESSION,
    MINUS_EXPRESSION,
    INCREMENT_EXPRESSION,
    DECREMENT_EXPRESSION,
    INDEX_EXPRESSION,
    METHOD_CALL_EXPRESSION,
    FUNCTION_CALL_EXPRESSION
} ExpressionType;

typedef struct {
    Expression  *left;
    Expression  *right;
} AssignExpression;

typedef struct {
    Expression      *left;
    Expression      *right;
} BinaryExpression;

typedef struct {
    char            *identifier;
    ArgumentList    *args;
} FunctionCallExpression;

typedef struct {
    Expression      *array;
    Expression      *idx;
} IndexExpression;

typedef struct {
    Expression      *expr;
    char            *identifier;
    ArgumentList    *args;
} MethodCallExpression;

typedef struct Expression_tag {
    ExpressionType type;
    int line_num;
    union {
        char                    *identifier;
        int                     int_val;
        double                  double_val;
        ABC_Char                *string_val;              
        ABC_Array               *array_val;

        AssignExpression        assign_expr;
        Expression              *singular_expr;
        BinaryExpression        binary_expr;
        FunctionCallExpression  func_expr;
        MethodCallExpression    method_call_expr;
        IndexExpression         index_expr;
    } u;
} Expression;

typedef enum {
    IF_STATEMENT,
    FOR_STATEMENT,
    WHILE_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT
} StatementType;

typedef struct ElseIfList_tag {
    Expression  *cond;
    Block       *block;
    struct ElseIfList_tag *next;
} ElseIfList;

typedef struct {
    Expression  *if_cond;
    Block       *if_block;
    ElseIfList  *elseif;
    Block       *else_block;
} IfStatement;  

typedef struct {
    Expression  *init;
    Expression  *cond;
    Expression  *post;
    Block       *block;
} ForStatement;

typedef struct {
    Expression  *cond;
    Block       *block;
} WhileStatement;

typedef struct {
    Expression *expr;
} ReturnStatement;

struct Statement_tag {
    StatementType type;
    int           line_num;
    union {
        Expression      *expr_stat;
        IdentifierList  *identifier_list;
        IfStatement     if_stat;
        ForStatement    for_stat;
        WhileStatement  while_stat;
        ReturnStatement return_stat;
    } u;
};

typedef struct StatementList_tag {
    Statement       *statement;
    StatementList   *next;
} StatementList;

typedef struct IdentifierList_tag {
    char *name;
    struct IdentifierList_tag *next;
} IdentifierList;

struct Block_tag {
    StatementList *statement_list;
};

typedef enum {
    NORMAL_STATEMENT_RESULT = 1,
    RETURN_STATEMENT_RESULT,
    BREAK_STATEMENT_RESULT,
    CONTINUE_STATEMENT_RESULT,
    STATEMENT_RESULT_TYPE_PLUS_1
} StatementResultType;

typedef struct {
    StatementResultType type;
    ABC_Value           value;
} StatementResult;

typedef struct {
    int         current_heap_size;
    int         threshold_size;
    ABC_Object  *front; 
} Heap;

typedef struct {
    int         pos;
    int         alloc_size;
    ABC_Value   *top;
} Stack;

typedef struct VariableList_tag {
    char                *identifier;
    ABC_Value           value;
    struct VariableList_tag *next;
} VariableList ;

typedef struct ParameterList_tag {
    char                *identifier;
    struct ParameterList *next;
} ParameterList ;

typedef struct ArgumentList_tag {
    Expression              *expr;
    struct ArugumentList_tag *next;
} ArgumentList;

typedef enum {
    SYSTEM_FUNCTION,
    USER_FUNCTION
} FunctionType;

typedef struct {
    ABC_Object *obj;
    RefInNativeMethod *next;
} RefInNativeMethod;

typedef struct {
    FunctionType type;
    char    *identifier;
    union {
        struct {
            ParameterList   *params;
            Block           *block;
        } user_function;
        struct {
            ABC_SystemFuncPorc *proc
        } system_function;
    } u;
} FunctionDefinition;

typedef struct LocalEnvironment_tag {
    VariableList        *local_variable;
    LocalEnvironment    *next;
} LocalEnvironment;

typedef struct ABC_interpreter_tag {
    int                 line_num;
    Heap                heap;
    Stack               stack;
    LocalEnvironment    *top_environment;
    VariableList        *global_variable;
    StatementList       *statement_list;
    FunctionDefinition  *func_list;
} ABC_interpreter;
     
#define abc_is_object(val) \
    (val->type == ABC_STRING_VALUE || val->type == ABC_ARRAY_VALUE\ 
        || val->type == ABC_MAP_VALUE)
#define abc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)

#define abc_is_compare_operator(operator) \
  ((operator) == EQ_EXPRESSION || (operator) == NE_EXPRESSION\
   || (operator) == GT_EXPRESSION || (operator) == GE_EXPRESSION\
   || (operator) == LT_EXPRESSION || (operator) == LE_EXPRESSION)

#define abc_is_logical_operator(operator) \
  ((operator) == LOGICAL_AND_EXPRESSION || (operator) == LOGICAL_OR_EXPRESSION)   
/* ablang.c */
ABC_interpreter *abc_get_interpreter();
int abc_get_line_number();

/* create.c */
void abc_create_function(char *identifier, ParameterList *parameter_list,
                         Block *block);
ParameterList *abc_create_parameter(char *identifier);
ParameterList *abc_chain_parameter(ParameterList *list,
                                   char *identifier);
ArgumentList *abc_create_argument_list(Expression *expression);
ArgumentList *abc_chain_argument_list(ArgumentList *list, Expression *expr);
StatementList *abc_create_statement_list(Statement *statement);
StatementList *abc_chain_statement_list(StatementList *list,
                                        Statement *statement);
Expression *abc_create_expression(ExpressionType type);
Expression *abc_create_assign_expression(char *variable,
                                             Expression *operand);
Expression *abc_create_binary_expression(ExpressionType type,
                                         Expression *left,
                                         Expression *right);
Expression *abc_create_singular_expression(ExpressionType type, Expression *operand);
Expression *abc_create_identifier_expression(char *identifier);
Expression *abc_create_function_call_expression(char *func_name,
                                                ArgumentList *argument);
Expression *abc_create_boolean_expression(abc_Boolean value);
Expression *abc_create_null_expression(void);
Statement *abc_create_global_statement(IdentifierList *identifier_list);
IdentifierList *abc_create_global_identifier(char *identifier);
IdentifierList *abc_chain_identifier(IdentifierList *list, char *identifier);
Statement *abc_create_if_statement(Expression *condition,
                                    Block *then_block, ElseIfList *elsif_list,
                                    Block *else_block);
ElseIfList *abc_chain_elseif(ElseIfList *list, ElseIfList *add);
ElseIfList *abc_create_elseif(Expression *expr, Block *block);
Statement *abc_create_while_statement(Expression *condition, Block *block);
Statement *abc_create_for_statement(Expression *init, Expression *cond,
                                    Expression *post, Block *block);
Block *abc_create_block(StatementList *statement_list);
Statement *abc_create_expression_statement(Expression *expression);
Statement *abc_create_return_statement(Expression *expression);
Statement *abc_create_break_statement(void);
Statement *abc_create_continue_statement(void);

/* string.c */
void abc_string_start();
void abc_string_add_char(char c);
char *abc_string_end();
char *abc_string_create_identifier(char *str);


#endif