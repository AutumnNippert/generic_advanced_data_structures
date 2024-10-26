// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "primitives.h"

typedef struct stack_node{
    void* val;
    size_t type_size;
    struct stack_node* next;
} stack_node_t;

typedef struct stack_stats{
    size_t pushes;
    size_t peeks;
    size_t pops;
} stack_stats_t;

typedef struct stack{
    size_t size;
    stack_node_t* head;
    size_t type_size;
    free_t free_func;
    stack_stats_t stats;
} stack_t;

stack_t* stack_create(size_t type_size, free_t);

void stack_push(stack_t*, void*);
void* stack_pop(stack_t*);
void* stack_peek(stack_t*);

void stack_free(stack_t*);

void stack_print_stats(stack_t*);