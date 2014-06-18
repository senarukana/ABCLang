#include "abclang.h"
#include <string.h>


/*
 * Use Heap to manage the Objects.
 * All the objects are chained in the heap.
 * Use mark-sweep to manage them.
 *
 */

static void check_gc() {
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    if (inter->heap.current_heap_size > inter->heap.threshold_size) {
        fprintf(stderr,"begin garbage collect, current size is %d\n", inter->heap.current_heap_size);
        abc_garbage_collect();
        fprintf(stderr,"end garbage collect, current size is %d\n", inter->heap.current_heap_size);
        inter->heap.threshold_size = inter->heap.current_heap_size + HEAP_THRESHOLDSIZE;
    }
}

/* protect the object in ref, in case it is collected by gc */ 
void abc_add_ref_in_native_method(LocalEnvironment *env, ABC_Object *obj) {
    RefInNativeFunc *new_ref;

    new_ref = MEM_malloc(sizeof(RefInNativeFunc));
    new_ref->object = obj;
    new_ref->next = env->ref_in_native_func;
    env->ref_in_native_func = new_ref;
}

ABC_Object *abc_alloc_object(ObjectType type) {
    ABC_Object *obj;
    ABC_Interpreter *inter;

    check_gc();
    inter = abc_get_interpreter();
    obj = MEM_malloc(sizeof(ABC_Object));
    obj->type = type;
    obj->prev = NULL;
    obj->next = inter->heap.front;
    inter->heap.front = obj;
    if (obj->next) {
        obj->next->prev = obj;
    }
    inter->heap.current_heap_size += sizeof(ABC_Object);
    return obj;
}

ABC_Object *abc_literal_to_object_string(ABC_Char *str) {
    ABC_Interpreter *inter;
    ABC_Object *obj;

    inter = abc_get_interpreter();
    obj = abc_alloc_object(STRING_OBJECT);
    obj->u.str.str = str;
    obj->u.str.is_literal = ABC_False;
    inter->heap.current_heap_size += sizeof(ABC_Char) * (abc_wcs_len(str) +1);

    return obj;
}

ABC_Object *abc_create_string_literal(ABC_Char *str) {
    ABC_Object *obj;

    obj = abc_alloc_object(STRING_OBJECT);
    obj->u.str.str = str;
    obj->u.str.is_literal = ABC_False;

    return obj;
}

ABC_Object *abc_create_string(ABC_Char *str) {
    ABC_Object *obj;
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    inter->heap.current_heap_size += abc_wcstombs_len(str);
    obj = abc_alloc_object(STRING_OBJECT);
    obj->u.str.is_literal = ABC_True;
    obj->u.str.str = str;

    return obj;
}

ABC_Object *abc_create_array_safe(int size) {
    ABC_Object *obj;
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    obj = abc_alloc_object(ARRAY_OBJECT);
    obj->u.array.size = size;
    obj->u.array.alloc_size = size;
    obj->u.array.array = MEM_malloc(sizeof(ABC_Value) * size);

    inter->heap.current_heap_size += sizeof(ABC_Value) * size;

    return obj;
}

ABC_Object *abc_create_array(LocalEnvironment *env, int size) {
    ABC_Object *obj;

    obj = abc_create_array_safe(size);
    abc_add_ref_in_native_method(env, obj);

    return obj;
}

ABC_Object *abc_create_assoc_safe() {
    ABC_Object *obj;

    obj = abc_alloc_object(ASSOC_OBJECT);
    obj->u.assoc.member_count = 0;
    obj->u.assoc.member = NULL;

    return obj;
}

ABC_Object *abc_create_assoc(LocalEnvironment *env) {
    ABC_Object *obj;

    obj = abc_create_assoc_safe();
    abc_add_ref_in_native_method(env, obj);

    return obj;
}

ABC_Value *abc_add_assoc_member(ABC_Object *assoc,
                     char *name, ABC_Value *value, ABC_Bool is_final) {
    AssocMember *member_p;
    ABC_Interpreter *inter;

    check_gc();
    inter = abc_get_interpreter();
    member_p = MEM_realloc(assoc->u.assoc.member,
                           sizeof(AssocMember)
                           * (assoc->u.assoc.member_count+1));
    member_p[assoc->u.assoc.member_count].name = name;
    member_p[assoc->u.assoc.member_count].value = *value;
    member_p[assoc->u.assoc.member_count].is_final = is_final;
    assoc->u.assoc.member = member_p;
    assoc->u.assoc.member_count++;
    inter->heap.current_heap_size += sizeof(AssocMember);

    return &member_p[assoc->u.assoc.member_count-1].value;
}

void abc_add_assoc_member2(ABC_Object *assoc,
                      char *name, ABC_Value *value) {
    int i;

    if (assoc->u.assoc.member_count > 0) {
        for (i = 0; i < assoc->u.assoc.member_count; i++) {
            if (!strcmp(assoc->u.assoc.member[i].name, name)) {
                break;
            }
        }
        if (i < assoc->u.assoc.member_count) {
            /* update it */
            assoc->u.assoc.member[i].value = *value;
            return;
        }
    }
    abc_add_assoc_member(assoc, name, value, ABC_False);
}

ABC_Value *abc_search_assoc_member(ABC_Object *assoc, char *member_name) {
    ABC_Value *ret = NULL;
    int i;

    if (assoc->u.assoc.member_count == 0)
        return NULL;

    for (i = 0; i < assoc->u.assoc.member_count; i++) {
        if (!strcmp(assoc->u.assoc.member[i].name, member_name)) {
            ret = &assoc->u.assoc.member[i].value;
            break;
        }
    }

    return ret;
}

ABC_Value *abc_search_assoc_member_w(ABC_Object *assoc, char *member_name,
                          ABC_Bool *is_final) {
    ABC_Value *ret = NULL;
    int i;

    if (assoc->u.assoc.member_count == 0)
        return NULL;

    for (i = 0; i < assoc->u.assoc.member_count; i++) {
        if (!strcmp(assoc->u.assoc.member[i].name, member_name)) {
            ret = &assoc->u.assoc.member[i].value;
            *is_final = assoc->u.assoc.member[i].is_final;
            break;
        }
    }
    return ret;
}

ABC_Object *abc_create_scope_chain() {
    ABC_Object *ret;

    ret = abc_alloc_object(SCOPE_CHAIN_OBJECT);
    ret->u.scope_chain.frame = NULL;
    ret->u.scope_chain.next = NULL;

    return ret;
}

static void dispose_object(ABC_Object *obj) {
    ABC_Interpreter *inter;

    inter = abc_get_interpreter();
    switch(obj->type) {
    case ARRAY_OBJECT:
        fprintf(stderr,"dispose array\n");
        break;
    case STRING_OBJECT:
        if (!obj->u.str.is_literal) {
            inter->heap.current_heap_size -= sizeof(ABC_Char) * abc_wcs_len(obj->u.str.str);
            free(obj->u.str.str);
        }
        break;
    default:
        abc_internal_error(-1, UNKNOWN_VALUE_TYPE_ERR);
    }
    inter->heap.current_heap_size -= sizeof(ABC_Object);
    free(obj);
}

static void gc_sweep() {
    ABC_Interpreter *inter;
    ABC_Object *obj, *tmp;

    inter = abc_get_interpreter();

    obj = inter->heap.front;

    while (obj != NULL) {
        if (!obj->mark) {
            tmp = obj->next;
            if (obj->prev) {
                obj->prev->next = obj->next;
            } else {
                inter->heap.front = tmp;
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
    VariableList       *vp;
    ABC_Value           *val;
    ABC_Object          *obj;
    int i;

    inter = abc_get_interpreter();

    /*reset mark*/
    for (obj = inter->heap.front; obj; obj = obj->next) {
        obj->mark = ABC_False;
    }

    /*global variable*/
    for (vp = inter->global_variable; vp; vp = vp->next) {
        val = &vp->value;
        if (abc_is_object(val)) {
            val->u.object->mark = ABC_True;
        }
    }

    /*local variable*/
    for (lp = inter->top_environment; lp; lp = lp->next) {
        for (vp = lp->local_variable; vp; vp = vp->next) {
            val = &vp->value;
            if (abc_is_object(val)) {
                val->u.object->mark = ABC_True;
            }
        }
    }

    /*stack variable*/
    for (i = 0; i < inter->stack.pos; i++) {
        val = &inter->stack.top[i];
        if (abc_is_object(val)) {
            val->u.object->mark = ABC_True;
        }
    }
}

void abc_garbage_collect() {
    gc_mark();
    gc_sweep();
}