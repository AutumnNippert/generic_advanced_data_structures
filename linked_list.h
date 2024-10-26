// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "primitives.h"

typedef struct linked_list_node{
    void* val;
    size_t type_size;
    struct linked_list_node* next;
    struct linked_list_node* prev;
} linked_list_node_t;

typedef struct linked_list{
    size_t size;
    linked_list_node_t* head;
    linked_list_node_t* tail;
    size_t type_size;
    compare_t compare_func;
    free_t free_func;
} linked_list_t;

linked_list_t* linked_list_create(size_t type_size, free_t);

void linked_list_add(linked_list_t*, void*);
void linked_list_add_sorted(linked_list_t*, void*, compare_t);
int linked_list_add_if_not_contains(linked_list_t*, void*, compare_t);

void* linked_list_get(linked_list_t*, size_t);
void linked_list_remove(linked_list_t*, void*, compare_t);

void linked_list_sort(linked_list_t*, compare_t);

void linked_list_free(linked_list_t*);

int linked_list_contains(linked_list_t*, void*, compare_t);

void print_stats();