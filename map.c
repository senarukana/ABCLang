#include <stdio.h>
#include <string.h>
#include "abclang.h"

static unsigned long next_power(unsigned long n) {
    unsigned long p;
    p = 1;
    while (p < n) {
        p *= 2;
    }
    return p;
}

unsigned long hash_algo(const char *buf) {
    unsigned long hash = 1379;
    int i, len;
    len = strlen(buf);
    for (i = 0; i < len; i++) {
        hash = ((hash<<5) + hash) + buf[i];
    }
    return hash;
}

unsigned long hash_func(ABC_Value *key) {
    unsigned long hash = 0;
    char *buf = NULL;

    switch (key->type) {
    case ABC_INT_VALUE:
        return key->u.int_val;
    case ABC_DOUBLE_VALUE:
        buf = (char*)MEM_malloc(50*sizeof(char));
        hash = hash_algo(buf);
    case ABC_STRING_VALUE:
        buf = abc_wcstombs_alloc(key->u.object->u.str.str);
        hash = hash_algo(buf);
    default:
        abc_internal_error(-1, INVALID_TYPE_ERR);
    }

    free(buf);
    return hash;
}

static void reset_hashmap(hashmap *map) {
    map->table = NULL;
    map->buck_num = 0;
    map->mask = 0;
    map->size = 0;
}

static void _map_rehash(ABC_Map *map) {
    hashnode *node, *tmp;
    
    if (map->ht[0].size == 0) {
        free(map->ht[0].table);
        map->ht[0] = map->ht[1];
        reset_hashmap(&map->ht[1]);
        map->rehash_idx = -1;
        return;
    }
    node = map->ht[0].table[map->rehash_idx]; 
    while (node) {
        tmp = node->next;
        node->next = map->ht[1].table[map->rehash_idx];
        map->ht[1].table[map->rehash_idx] = node;
        node = tmp;
        map->ht[0].size--;
        map->ht[1].size++;
    }
    map->rehash_idx++;
}

static void map_rehash(ABC_Map *map) {
    if (map_is_rehashing(map)) {
        _map_rehash(map);
    }
}

static void create_hashmap_nodes(hashmap *ht, int size) {
    int i;
    ht->table = MEM_malloc(size*sizeof(hashnode*));
    for (i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    ht->buck_num = size;
    ht->mask = size-1;
    ht->size = 0;
}

static void map_expand(ABC_Map *map) {
    create_hashmap_nodes(&map->ht[1], next_power(map->ht[0].size));
    map->rehash_idx = 0;
}

static void map_expand_if_needed(ABC_Map *map) {
    if (map_is_rehashing(map)) {
        return;
    }
    if (map->ht[0].buck_num == 0) {
        create_hashmap_nodes(&map->ht[0], MAP_INITIAL_SIZE);
        return;
    }
    if ((double)map->ht[0].buck_num * MAP_EXPAND_RATIO < (double)map->ht[0].size ) {
        map_expand(map);
    }
}

static hashnode *new_hashnode(ABC_Value *key, ABC_Value *val) {
    hashnode *new_node;

    new_node = (hashnode*)MEM_malloc(sizeof(hashnode));
    new_node->key = *key;
    new_node->val = *val;
    new_node->next = NULL;
    return new_node;
}

ABC_Object *abc_create_hashmap_safe() {
    ABC_Object *obj;
    obj = abc_alloc_object(MAP_OBJECT);
    obj->u.map.size = 0;
    obj->u.map.rehash_idx = -1;
    reset_hashmap(&obj->u.map.ht[0]);
    reset_hashmap(&obj->u.map.ht[1]);

    return obj;
}

ABC_Object *abc_create_hashmap(LocalEnvironment *env) {
    ABC_Object *obj;

    obj = abc_create_hashmap_safe();
    abc_add_ref_in_native_method(env, obj);

    return obj;
}

ABC_Value abc_hashmap_set(ABC_Object *m, ABC_Value *key, ABC_Value *val) {
    ABC_Map *map;
    ABC_Value old_val;
    hashnode *node, *new_node;
    unsigned long hash;
    int idx, table = 0;

    map =  &m->u.map;
    map_expand_if_needed(map);
    hash = hash_func(key);

    for (table = 0; table <= 1; table++) {
        idx = hash & map->ht[table].mask;
        for (node = map->ht[table].table[idx]; node; node = node->next) {
            if (abc_value_compare(key, &node->key) == 0) {
                old_val = node->val;
                node->val = *val;
                return old_val;
            }
        }
        if (!map_is_rehashing(map)) {
            break;
        }
    }
    new_node = new_hashnode(key, val);
    new_node->next = map->ht[table].table[idx];
    map->ht[table].table[idx] = new_node;
    map->ht[table].size++;
    map->size++;
    return new_node->val;
}

ABC_Value *abc_hashmap_get(ABC_Object *m, ABC_Value *key) {
    ABC_Map *map;
    hashnode *node;
    unsigned long hash;
    int idx, table = 0;

    map = &m->u.map;
    map_rehash(map);

    hash = hash_func(key);
    for (table = 0; table <= 1; table++) {
        idx = hash & map->ht[table].mask;
        for (node = map->ht[table].table[idx]; node != NULL; node = node->next) {
            if (abc_value_compare(key, &(node->key)) == 0) {
                return &node->val;
            }
        }
        if (!map_is_rehashing(map)) {
            break;
        }
    }
    return NULL;
}

int abc_hashmap_delete(ABC_Object *m, ABC_Value *key) {
    ABC_Map *map;
    hashnode *node, *prev = NULL;
    unsigned long hash;
    int idx, table = 0;

    map = &m->u.map;
    map_rehash(map);

    hash = hash_func(key);
    
    for (table = 0; table <= 1; table++) {
        idx = hash & map->ht[table].mask;
        for (node = map->ht[table].table[idx]; node; prev = node, node = node->next) {
            if (abc_value_compare(key, &node->key) == 0) {
                /* header */
                if (prev == NULL) {
                    map->ht[table].table[idx] = node->next;
                } else {
                    prev->next = node->next;
                }
                free(node);
                return 0;
            }
        }
        if (!map_is_rehashing(map)) {
            break;
        }
    }
    /* not found it */ 
    return -1;
}

int main() {

    ABC_Object *obj;
    ABC_Value k1, v1, k2, v2;
    k1.type = ABC_INT_VALUE;
    k1.u.int_val = 3;
    v1.type = ABC_DOUBLE_VALUE;
    v1.u.double_val = 1.8;
    k2.type = ABC_INT_VALUE;
    k2.u.int_val = 4;
    v2.type = ABC_DOUBLE_VALUE;
    v2.u.double_val = 2.8;

    ABC_create_interpreter();

    obj = abc_create_hashmap_safe();
    abc_hashmap_set(obj, &k1, &v1);
    abc_hashmap_set(obj, &k2, &v2);
    printf("size = %lu\n", obj->u.map.size);
    printf("%f\n",abc_hashmap_get(obj, &k1)->u.double_val);
    abc_hashmap_delete(obj, &k1);
    if (abc_hashmap_get(obj, &k1) != NULL) {
        printf("system error\n");
    }
}