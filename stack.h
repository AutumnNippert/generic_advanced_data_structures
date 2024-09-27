// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef int (*equals_t)(void*, void*);
typedef int (*compare_t)(void*, void*);
typedef int (*type_check_t)(void*);
typedef int (*hash_t)(void*);
typedef void (*free_t)(void*);

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
    equals_t equals_func;
    type_check_t type_check_func;
    free_t free_func;
    stack_stats_t stats;
} stack_t;

stack_t* stack_create(size_t type_size, equals_t, type_check_t, free_t );

void stack_push(stack_t* stack, void* val);
void* stack_pop(stack_t* stack);
void* stack_peek(stack_t* stack);

void stack_free(stack_t* stack);

void stack_print_stats(stack_t* stack);