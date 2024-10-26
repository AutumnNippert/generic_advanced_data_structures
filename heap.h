#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "primitives.h"
#include "dsa.h"

// binary heap
typedef struct heap{
    size_t type_size;
    compare_t compare;
    free_t free;
    dsa_t* arr;
    size_t size;
    size_t capacity;
}heap_t;

heap_t* heap_create(size_t type_size, compare_t compare, free_t free);
heap_t* heapify(size_t type_size, compare_t compare, free_t free, dsa_t* arr, size_t size);
void heap_push(heap_t* heap, void* val);
void* heap_peek(heap_t* heap);
void* heap_pop(heap_t* heap);

void heap_free(heap_t* heap);

void heap_print(heap_t* heap);