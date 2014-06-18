#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "memory.h"

static void default_error_handler(MEM_Controller *controller,
                                  char *filename, int line, char *msg);

static MEM_Controller default_controller = {
    NULL,/* stderr */
    default_error_handler,
    MEM_FAIL_AND_EXIT
};
MEM_Controller *mem_default_controller = &default_controller;

static void default_error_handler(MEM_Controller *controller, 
            char *filename, int line, char *msg) {
    fprintf(controller->error_fp,
            "MEM:%s failed in %s at %d line\n", msg, filename, line);
}

static void error_handler(MEM_Controller *controller,
            char *filename, int line, char *msg) {
    if (controller->error_fp == NULL) {
        controller->error_fp = stderr;
    }
    controller->error_handler(controller, filename, line, msg);
    if (controller->error_mode == MEM_FAIL_AND_EXIT) {
        exit(1);
    }
}

void *MEM_malloc_func(MEM_Controller *controller, 
            char *filename, int line,  size_t size) {
    void    *ptr;
    
    ptr = malloc(size);
    if (ptr == NULL) {
        error_handler(controller, filename, line, "malloc");
    }

    return ptr;
}

void *MEM_calloc_func(MEM_Controller *controller, 
            char *filename, int line, size_t count, size_t size) {
    void    *ptr;
    
    ptr = calloc(count, size);
    if (ptr == NULL) {
        error_handler(controller, filename, line, "calloc");
    }

    return ptr;
}

void *MEM_realloc_func(MEM_Controller *controller, 
            char *filename, int line, void *ptr, size_t size) {
    void    *new_ptr;
    
    new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        error_handler(controller, filename, line, "realloc");
    }
    return new_ptr;
}

MEM_Controller *MEM_create_controller(void) {
    MEM_Controller  *controller;

    controller = MEM_malloc_func(mem_default_controller, 
                __FILE__, __LINE__, sizeof(MEM_Controller));
    *controller = default_controller;
    return controller;
}

MEM_Storage *MEM_open_storage_func(MEM_Controller *controller,
        char *filename, int line, int page_size) {
    MEM_Storage *storage;

    storage = MEM_malloc_func(controller, filename, line, page_size);
    if (page_size == 0) {
        storage->page_size = DEFAULT_PAGE_SIZE;
    } else {
        storage->page_size = page_size;
    }
    storage->page_num = 0;
    storage->page_list = NULL;

    return storage; 
}

void *MEM_storage_malloc_func(MEM_Controller *controller, MEM_Storage *storage,
        char *filename, int line, size_t size) {
    MemoryPage  *new_page, *page;
    void *p;

    if (size > storage->page_size) {
        error_handler(controller, filename, line, "Request Memoery Too Big");
        return NULL; 
    }

    // check if there is enough space in page_list 
    for (page = storage->page_list; page != NULL; page = page->next) {
        if (page->pos + PAGE_HEADER_SIZE + size <= storage->page_size) {
            break;
        }
    }
    // found free space in page lsit
    if (page != NULL) {
        p = &(page->memory[page->pos]);
        page->pos += size;
    } else {
        // alloc a new page
        new_page = MEM_malloc_func(controller,
            filename, line, storage->page_size);
        new_page->pos = size;
        new_page->next = storage->page_list;
        storage->page_list = new_page;
        storage->page_num++;
        p = &(new_page->memory[0]);
    }
    return p;
}



void MEM_dispose_storage_func(MEM_Controller *controller, MEM_Storage *storage) {
    MemoryPage *page;
    while (storage->page_list) {
        page = storage->page_list->next;
        free(storage->page_list);
        storage->page_list = page;
    }
    free(storage);
}