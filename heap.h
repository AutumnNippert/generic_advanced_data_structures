#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "prim_functions.h"

// binary heap
typedef struct heap_node{
    void* val;
    struct heap_node* parent;
    struct heap_node* left;
    struct heap_node* right;
} heap_node_t;

typedef struct heap{
    size_t size;
    size_t type_size;
    compare_t compare_func;
    free_t free_func;
    heap_node_t* root;
} heap_t;

heap_t* heap_create(size_t type_size, compare_t compare, free_t free);
void heap_push(heap_t* heap, void* val);
void* heap_peek(heap_t* heap);
void* heap_pop(heap_t* heap);

void heap_free(heap_t* heap);