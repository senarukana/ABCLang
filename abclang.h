#ifndef ABC_PRIVATE__
#define ABC_PRIVATE__
#include <wchar.h>
#include "./memory/memory.h"

#define HEAP_ALLOC_SIZE     (1024 * 32)
#define STACK_ALLOC_SIZE    (1024 * 32)
#define LINE_BUF_SIZE       (256)
#define HEAP_THRESHOLDSIZE  (1024 * 256)
#define MAP_EXPAND_RATIO (1.7)
#define MAP_INITIAL_SIZE (8)

typedef struct ABC_Value_tag ABC_Value;
typedef struct ABC_Object_tag ABC_Object;
typedef struct ABC_Map_tag  ABC_Map;      
typedef struct ABC_Assoc_tag ABC_Assoc;
typedef struct Expression_tag Expression;
typedef struct Statement_tag  Statement;
typedef struct ParameterList_tag ParameterList;
typedef struct ArgumentList_tag ArgumentList;
typedef struct StatementList_tag StatementList;
typedef struct IdentifierList_tag IdentifierList;
typedef struct LocalEnvironment_tag LocalEnvironment;
typedef struct ExpressionList_tag ExpressionList;
typedef struct Block_tag Block;
typedef struct FunctionDefinition_tag FunctionDefinition;
typedef struct ABC_Interpreter_tag ABC_Interpreter;

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
    ABC_MAP_VALUE,
    ABC_ASSOC_VALUE,
} ABC_ValueType;

typedef enum {
    ARRAY_OBJECT = 1,
    STRING_OBJECT,
    ASSOC_OBJECT,
    SCOPE_CHAIN_OBJECT,
    MAP_OBJECT
} ObjectType;

struct ABC_Value_tag {
    ABC_ValueType type;
    union {
        int         int_val;
        double      double_val;
        ABC_Bool    bool_val;
        ABC_Pointer pointer;
        ABC_Object  *object;
    }u;
};

typedef struct {
    char        *name;
    ABC_Value   value;
    ABC_Bool    is_final;
} AssocMember;

struct ABC_Assoc_tag {
    int             member_count;
    AssocMember     *member; 
};

typedef struct {
    ABC_Object  *frame; /* ABC_Assoc */
    ABC_Object  *next;  /* ScopeChain */
} ScopeChain;

typedef struct {
    FunctionDefinition  *func;
    ABC_Object          *environment; /* Scope Chain */
} ABC_Lambda;

typedef struct hashnode_tag {
    ABC_Value   key;
    ABC_Value   val;
    struct hashnode_tag *next;
} hashnode;

typedef struct hashmap_tag {
    hashnode    **table;
    unsigned long buck_num;
    unsigned long mask;
    unsigned long size;
} hashmap;

struct ABC_Map_tag {
    hashmap ht[2];
    int rehash_idx;
    unsigned long size;
};

typedef struct ABC_String_tag {
    int         is_literal;
    ABC_Char    *str;
} ABC_String;

typedef struct ABC_Array_tag {
    int         size;
    int         alloc_size;
    ABC_Value   *array;
} ABC_Array;

struct ABC_Object_tag {
    ObjectType      type;
    int             mark:1;
    union {
        ABC_String  str;
        ABC_Array   array;
        ABC_Assoc   assoc;
        ScopeChain  scope_chain;
        ABC_Map     map;
    } u;
    struct ABC_Object_tag *prev;
    struct ABC_Object_tag *next;
};

/* Error */
typedef struct {
    char *format;
} MessageFormat;

typedef enum {
    PARSE_ERR = 1,
    FUNCTION_MULTIPLE_DEFINE_ERR,
    STATEMENT_TOO_LONG_ERR,
    INVALID_CHARACTER_ERR
} CompileErrorType;

typedef enum {
    VARIABLE_NOT_FOUND_ERR = 1,
    VARIABLE_MULTIPLE_DEFINE_ERR,
    UNCOMPARABLE_EXPRESSION_ERR,
    FUNCTION_NOT_FOUND_ERR,
    GLOBAL_VARIABLE_CONTRADICT_ERR,
    ARGUMENT_TOO_MANY_ERR,
    ARGUMENT_TOO_FEW_ERR,
    INVALID_LVALUE_ERR,
    INVALID_INCR_OR_DECR_OPERATOR_ERR,
    ASSIGN_EXPRESSION_ERR,
    BAD_OPERATOR_FOR_STRING_ERR,
    NULL_OPERATOR_ERR,
    INCOMPATIBLE_VARIABLE_TYPE_ERR,
    MINUS_OPERATOR_ERR,
    INCR_OPERATOR_ERR,
    DIV_ZERO_ERR,
    NOT_BOOLEAN_TYPE_ERR,
    BAD_CHARACTER_ERR,
    INFINITE_WHILE_LOOP_ERR,
    INVALID_ARRAY_EXPRESSION_ERR,
    ARRAY_INDEX_OUT_OF_RANGE,
    NO_MEMBER_TYPE_ERR,
    NOT_OBJECT_MEMBER_ASSIGN_ERR,
    NO_SUCH_MEMBER_ERR
} RuntimeErrorType;

typedef enum {
    UNKNOWN_EXPRESSION_TYPE_ERR = 1,
    UNKNOWN_STATEMENT_TYPE_ERR,
    UNKNOWN_VALUE_TYPE_ERR,
    UNCOMPARABLE_TYPE,
    INVALID_TYPE_ERR,
} InternalErrorType;

/* Expression Definition */

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
    MOD_EXPRESSION,
    MINUS_EXPRESSION,
    INCREMENT_EXPRESSION,
    DECREMENT_EXPRESSION,
    INDEX_EXPRESSION,
    MEMBER_EXPRESSION,
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

typedef struct {
    Expression      *expr;
    char            *member_name;
} MemberExpression;

struct Expression_tag {
    ExpressionType type;
    int line_num;
    union {
        char                    *identifier;
        int                     int_val;
        double                  double_val;
        ABC_Bool                bool_val;
        ABC_Char                *string_val;              

        ExpressionList          *array_expr;
        AssignExpression        assign_expr;
        Expression              *singular_expr;
        BinaryExpression        binary_expr;
        FunctionCallExpression  func_expr;
        MemberExpression        member_expr;
        MethodCallExpression    method_call_expr;
        IndexExpression         index_expr;
    } u;
};

struct ExpressionList_tag {
    Expression *expr;
    struct ExpressionList_tag *next;
};

typedef enum {
    EXPRESSION_STATEMENT = 1,
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

struct StatementList_tag {
    Statement       *statement;
    struct StatementList_tag   *next;
};

struct IdentifierList_tag {
    char *name;
    struct IdentifierList_tag *next;
};

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
} VariableList;

struct ParameterList_tag {
    char                *identifier;
    struct ParameterList_tag *next;
};

struct ArgumentList_tag {
    Expression              *expr;
    struct ArgumentList_tag *next;
};

typedef enum {
    SYSTEM_FUNCTION,
    USER_FUNCTION
} FunctionType;


struct FunctionDefinition_tag{
    FunctionType type;
    char    *identifier;
    union {
        struct {
            ParameterList   *params;
            Block           *block;
        } user_function;
        struct {
            ABC_SystemFuncPorc *proc;
        } system_function;
    } u;
    struct FunctionDefinition_tag *next;
} ;

typedef struct RefInNativeFunc_tag {
    ABC_Object  *object;
    struct RefInNativeFunc_tag *next;
} RefInNativeFunc;

struct LocalEnvironment_tag {
    char                *fuc_name;
    int                 caller_line_number;
    VariableList        *local_variable;
    RefInNativeFunc     *ref_in_native_func;
    LocalEnvironment    *next;
};

struct ABC_Interpreter_tag {
    int                 line_num;
    MEM_Storage         *interpreter_storage;
    MEM_Storage         *execute_storage;
    Heap                heap;
    Stack               stack;
    LocalEnvironment    *top_environment;
    VariableList        *global_variable;
    StatementList       *statement_list;
    FunctionDefinition  *func_list;
};
     
#define abc_is_object(val) \
    (val->type == ABC_STRING_VALUE || val->type == ABC_ARRAY_VALUE\
     || val->type == ABC_MAP_VALUE)
#define abc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)

#define abc_is_compare_operator(operator) \
  ((operator) == EQUAL_EXPRESSION || (operator) == NOT_EQUAL_EXPRESSION\
   || (operator) == GT_EXPRESSION || (operator) == GE_EXPRESSION\
   || (operator) == LT_EXPRESSION || (operator) == LE_EXPRESSION)

#define abc_is_logical_operator(operator) \
  ((operator) == LOGICAL_AND_EXPRESSION || (operator) == LOGICAL_OR_EXPRESSION)   

#define map_is_rehashing(map) (map->rehash_idx >= 0)
/* abc.c */
ABC_Interpreter *abc_get_interpreter();
int abc_get_line_number();
ABC_Interpreter *ABC_create_interpreter();
void ABC_compile(ABC_Interpreter *inter, FILE *fp);
void ABC_execute(ABC_Interpreter *inter);

/* eval.c */
ABC_Value abc_eval_expression(LocalEnvironment *env, Expression *expr);

/* execute.c */
StatementResult abc_execute_statement_list(LocalEnvironment *env, StatementList *list);

/* heap.c */
void abc_garbage_collect();
ABC_Object *abc_alloc_object(ObjectType type);
ABC_Value *abc_search_assoc_member(ABC_Object *assoc, char *member_name);
void abc_add_ref_in_native_method(LocalEnvironment *env, ABC_Object *obj);
ABC_Object *abc_create_string(ABC_Char *str);
ABC_Object *abc_create_array_safe(int size);
ABC_Object *abc_create_array(LocalEnvironment *env, int size);
ABC_Object *abc_create_string_literal(ABC_Char *str);
ABC_Object *abc_literal_to_object_string(ABC_Char *str);

/* stack.c */
void abc_stack_push_value(ABC_Value *value);
ABC_Value abc_stack_pop_value();
void abc_stack_shrink(int num);
ABC_Value *abc_stack_peek(int idx);

/* create.c */
void abc_create_function(char *identifier, ParameterList *parameter_list,
                         Block *block);
ParameterList *abc_create_parameter(char *identifier);
ParameterList *abc_chain_parameter(ParameterList *list,
                                   char *identifier);
ArgumentList *abc_create_argument(Expression *expression);
ArgumentList *abc_chain_argument(ArgumentList *list, Expression *expr);
ExpressionList *abc_create_expression_list(Expression *expr);
ExpressionList *abc_chain_expression_list(ExpressionList *list, Expression *expr);
Block *abc_create_block(StatementList *statement_list);

Expression *abc_create_expression(ExpressionType type);
Expression *abc_create_assign_expression(Expression *left, Expression *right);
Expression *abc_create_binary_expression(ExpressionType type,
                                         Expression *left,
                                         Expression *right);
Expression *abc_create_singular_expression(ExpressionType type, Expression *operand);
Expression *abc_create_identifier_expression(char *identifier);
Expression *abc_create_function_call_expression(char *func_name,
                                                ArgumentList *argument);
Expression *abc_create_method_call_expression(Expression *expression, 
                char *identifier, ArgumentList *args); 
Expression *abc_create_index_expression(Expression *arr_expr, Expression *idx_expr);
Expression *abc_create_int_expression(int val);
Expression *abc_create_double_expression(double val);
Expression *abc_create_string_expression(ABC_Char *str);
Expression *abc_create_boolean_expression(ABC_Bool value);
Expression *abc_create_null_expression(void);
Expression *abc_create_array_expression(ExpressionList *list);
Expression *abc_create_member_expression(Expression *expr, char *member_name);

StatementList *abc_create_statement_list(Statement *statement);
StatementList *abc_chain_statement_list(StatementList *list,
                                        Statement *statement);
Statement *abc_create_if_statement(Expression *condition,
                                    Block *then_block, ElseIfList *elsif_list,
                                    Block *else_block);
ElseIfList *abc_chain_elseif(ElseIfList *list, ElseIfList *elseif);
ElseIfList *abc_create_elseif(Expression *expr, Block *block);
Statement *abc_create_while_statement(Expression *condition, Block *block);
Statement *abc_create_for_statement(Expression *init, Expression *cond,
                                    Expression *post, Block *block);
Statement *abc_create_expression_statement(Expression *expression);
Statement *abc_create_return_statement(Expression *expression);
Statement *abc_create_break_statement(void);
Statement *abc_create_continue_statement(void);

/* util.c */
void abc_add_global_variable(char *identifier, ABC_Value *value);
void abc_add_local_variable(LocalEnvironment *env, char *identifier, ABC_Value *value);
int abc_value_compare(ABC_Value *a, ABC_Value *b);

/* memory.c */
void *abc_storage_malloc(size_t size);
void *abc_execute_malloc(size_t size);

/* native.c */
ABC_Value abc_sys_print_proc(LocalEnvironment *env, 
                int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_sys_println_proc(LocalEnvironment *env, 
                int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_sys_fopen_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_sys_fclose_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num);
/*ABC_Value abc_sys_fread_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_sys_fwrite_proc(LocalEnvironment *env,
            int arg_count, ABC_Value *args, int line_num);*/
ABC_Value abc_sys_fgets_proc(LocalEnvironment *env, 
        int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_sys_fputs_proc(LocalEnvironment *env,
                  int arg_count, ABC_Value *args, int line_num);
ABC_Value abc_new_array_proc(LocalEnvironment *env, 
            int arg_count, ABC_Value *args, int line_num);
void abc_add_std_fp();

/* string.c */
void abc_string_start();
void abc_string_add_char(char c);
ABC_Char *abc_string_end();
char *abc_string_create_identifier(char *str);
ABC_Char *abc_value_to_string(ABC_Value *value);

/* error.c */
void abc_compile_error(CompileErrorType type, char *msg);
void abc_runtime_error(int line_number,RuntimeErrorType type);
void abc_internal_error(int line_number, InternalErrorType type);

/* wchar.c */
ABC_Char *abc_wcs_concate(ABC_Char *left, ABC_Char *right);
int abc_wcs_cmp(ABC_Char *left, ABC_Char *right);
int abc_wcs_len(ABC_Char *str);
ABC_Char *abc_wcs_cpy(ABC_Char *dest, ABC_Char *src);
int abc_wcstombs_len(const ABC_Char *src);
int abc_wcstombs(const ABC_Char *src, char *dest);
char *abc_wcstombs_alloc(const ABC_Char *src);
char *abc_wcsntombs_alloc(const ABC_Char *src, int len);
int abc_mbstowcs_len(const char *src);
void abc_mbstowcs(const char *src, ABC_Char *dest);
void abc_mbsntowcs(const char *src, int len, ABC_Char *dest);
ABC_Char *abc_mbstowcs_alloc(const char *src);
int abc_wcs_print(FILE *fp, ABC_Char *str);
int abc_wcs_println(FILE *fp, ABC_Char *str);

/* map.c */
unsigned long hash_func(ABC_Value *key);

ABC_Object *abc_create_hashmap_safe();
ABC_Object *abc_create_hashmap(LocalEnvironment *env);
ABC_Value abc_hashmap_set(ABC_Object *m, ABC_Value *key, ABC_Value *val);
ABC_Value *abc_hashmap_get(ABC_Object *m, ABC_Value *key);
int abc_hashmap_delete(ABC_Object *m, ABC_Value *key);


#endif
