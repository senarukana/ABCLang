#include "abclang.h"

static void check_gc() {
    ABC_Intepreter *inter;

    inter = abc_get_interpreter();
    // check if the heap is big enough
    if (inter->heap.current_heap_size + size > inter->heap.threshold_size) {
        fprintf(stderr,"begin garbage collect, current size is %d\n", inter->heap.current_heap_size);
        abc_garbage_collect();
        fprintf(stderr,"end garbage collect, current size is %d\n", inter->heap.current_heap_size);
        inter->heap.threshold_size = inter->heap.current_heap_size + HEAP_THRESHOLDSIZE;
    }
}

static ABC_Object *alloc_object(ObjectType type) {
    ABC_Object *obj;

    check_gc();
    obj = abc_execute_malloc(sizeof(ABC_Object));
    obj->type = type;
    obj->prev = NULL;
    obj->next = abc_get_interpreter()->heap.top;
    abc_get_interpreter()->heap.top = obj;
    if (obj->next) {
        obj->next->prev = obj;
    }

    return obj;
}

ABC_Object *abc_literal_to_object_string(ABC_Char *str) {
    ABC_Interpreter *inter;
    ABC_Object *obj;

    inter = abc_get_interpreter();
    obj = alloc_object(STRING_OBJECT);
    obj->str.str = str;
    obj->u.str.is_literal = ABC_False;
    inter->heap.current_heap_size += sizeof(ABC_Char) * (abc_wcs_len(str) +1);

    return obj;
}

ABC_Object *abc_create_string_literal(ABC_Char *str) {
    ABC_Object *obj;

    obj = alloc_object(STRING_OBJECT);
    obj->u.str.str = str;
    obj->u.str.is_literal = ABC_False;

    return obj;
}

ABC_Object *abc_create_string(ABC_Char *str) {
    ABC_Object *obj;
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    inter->heap.current_heap_size += abc_wcstombs_len(str);
    obj = alloc_object(STRING_OBJECT);
    obj->u.str.is_literal = ABC_True;
    obj->u.str.str = str;

    return obj;
}

static void dispose_object(ABC_Interpreter *inter, ABC_Object *obj) {
    switch(obj->type) {
    case ARRAY_OBJECT:

    case STRING_OBJECT:
        if (!obj->u.str.is_literal) {
            inter->heap.current_heap_size -= sizeof(ABC_Char) * abc_wcs_len(obj->u.str.str);
            free(obj->u.str.str);
        }
    default:
        abc_runtime_error();
    }
    inter->heap.current_heap_size -= sizeof(ABC_Object);
    free(obj);
}

static void gc_sweep() {
    ABC_Interpreter *inter;
    ABC_Object *obj, *tmp;

    inter = abc_get_interpreter();

    obj = inter->heap.front();

    while (obj->next != NULL) {
        if (!obj->object->mark) {
            tmp = obj->next;
            if (obj->prev) {
                obj->prev->next = obj->next;
            } else {
                inter->heap.top = tmp;
            }
            if (obj->next) {
                obj->next->prev = obj->prev;
            }
            dispose_object(obj);
            obj = tmp;
        } else {
            obj = obj->next;
        }
    }
}

static void gc_mark() {
    ABC_Interpreter     *inter;
    LocalEnvironment    *lp;
    VariabeleList       *vp;
    ABC_Value           *val;
    ABC_Object          *obj;
    int i;

    inter = abc_get_interpreter();

    // reset mark
    for (obj = inter->heap.header; obj; obj = obj->next) {
        obj->mark = ABC_False;
    }

    // global variable
    for (vp = inter->global_variable; vp; vp = vp->next) {
        val = &vp->value;
        if (abc_is_object(val)) {
            val->object->mark = ABC_True;
        }
    }

    // local variable
    for (lp = inter->top_environment; lp; lp = lp->next) {
        for (vp = lp->variable_list; vp; vp = vp->next) {
            val = &vp->value;
            if (abc_is_object(val)) {
                val->object->mark = ABC_True;
            }
        }
    }

    // stack variable
    for (i = 0; i < inter->stack.pos; i++) {
        val = inter->stack.top[i];
        if (abc_is_object(ABC_OBJECT_VALUE)) {
            val->object->mark = ABC_True;
        }
    }
}

void abc_garbage_collect() {
    gc_mark();
    gc_sweep();
}