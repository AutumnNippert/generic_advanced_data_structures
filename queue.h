// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "primitives.h"

typedef struct queue_node{
    void* val;
    size_t type_size;
    struct queue_node* next;
    struct queue_node* prev;
} queue_node_t;

typedef struct queue_stats{
    size_t enqueues;
    size_t peeks;
    size_t dequeues;
} queue_stats_t;

typedef struct queue{
    size_t size;
    queue_node_t* head;
    queue_node_t* tail;
    size_t type_size;
    free_t free_func;
    queue_stats_t stats;
} queue_t;

queue_t* queue_create(size_t type_size, free_t);

void queue_enqueue(queue_t*, void*);
void* queue_dequeue(queue_t*);
void* queue_peek(queue_t*);

void queue_free(queue_t*);

void queue_print_stats(queue_t*);