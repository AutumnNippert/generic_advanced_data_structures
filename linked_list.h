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
    equals_t equals_func;
    type_check_t type_check_func;
    free_t free_func;
} linked_list_t;

linked_list_t* linked_list_create(size_t type_size, equals_t, type_check_t, free_t );

void linked_list_add_sorted(linked_list_t* linked_list, void* val, compare_t compare);
void linked_list_sort(linked_list_t* linked_list, compare_t compare);

void linked_list_add(linked_list_t* linked_list, void* val);
int linked_list_add_if_not_contains(linked_list_t* linked_list, void* val);

void* linked_list_get_index(linked_list_t* linked_list, size_t index);
void* linked_list_get(linked_list_t* linked_list, void* val);

void linked_list_free(linked_list_t* linked_list);

int linked_list_hash(linked_list_t* linked_list, void* val);

bool linked_list_contains(linked_list_t* linked_list, void* val);

void linked_list_remove(linked_list_t* linked_list, void* val);

void print_stats();