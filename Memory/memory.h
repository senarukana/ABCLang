#ifndef MEMORY_HEADER__
#define MEMORY_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define PAGE_HEADER_SIZE            (sizeof(MemoryPage))
#define DEFAULT_PAGE_SIZE           (1024)
#define ALLOC_PAGE_SIZE(storage)    (storage->page_size-PAGE_HEADER_SIZE)
#define MEM_CURRENT_CONTROLLER mem_default_controller

typedef struct MEM_Controller_tag MEM_Controller;
typedef void (*MEM_ErrorHandler)(MEM_Controller *controller,
            char *filename, int line, char *msg);
typedef struct MEM_Storage_tag MEM_Storage;

typedef enum {
    MEM_FAIL_AND_EXIT,
    MEM_FAIL_AND_RETURN
} MEM_FailMode;

struct MEM_Controller_tag {
    FILE                *error_fp;
    MEM_ErrorHandler    error_handler;
    MEM_FailMode        error_mode;
};

typedef struct MemoryPage_tag {
    int     pos;
    struct MemoryPage_tag *next;
    char    memory[1];
} MemoryPage;

struct MEM_Storage_tag {
    int     page_size;
    int     page_num;
    MemoryPage *page_list;
};

extern MEM_Controller *mem_default_controller;

/*
 * Don't use mem_*_func function.
 * There are private functions of MEM module.
 */
MEM_Controller *MEM_create_controller(void);
void *MEM_malloc_func(MEM_Controller *controller,
                      char *filename, int line, size_t size);
void *MEM_realloc_func(MEM_Controller *controller,
                       char *filename, int line, void *ptr, size_t size);
char *MEM_strdup_func(MEM_Controller *controller,
                      char *filename, int line, char *str);

MEM_Storage *MEM_open_storage_func(MEM_Controller *controller,
        char *filename, int line, int page_size);
void *MEM_storage_malloc_func(MEM_Controller *controller, MEM_Storage *storage, 
                              char *filename, int line, size_t size);
void MEM_dispose_storage_func(MEM_Controller *controller,
                              MEM_Storage *storage);

#define MEM_malloc(size)\
    (MEM_malloc_func(MEM_CURRENT_CONTROLLER, \
                    __FILE__, __LINE__, size))
#define MEM_realloc(ptr, size)\
    (MEM_realloc_func(MEM_CURRENT_CONTROLLER, \
                    __FILE__, __LINE__, ptr, size))

#define MEM_open_storage(page_size)\
    (MEM_open_storage_func(MEM_CURRENT_CONTROLLER, \
                    __FILE__, __LINE__, page_size))
#define MEM_storage_malloc(storage, size)\
    (MEM_storage_malloc_func(MEM_CURRENT_CONTROLLER, storage, \
                    __FILE__, __LINE__, size))
#define MEM_dispose_storage(storage)\
    (MEM_dispose_storage_func(MEM_CURRENT_CONTROLLER, storage))

#endif
