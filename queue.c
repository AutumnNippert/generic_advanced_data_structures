// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "queue.h"

void print_queue(queue_t* queue){
    queue_node_t* curr = queue->head;
    // print like [1, 2, 3]
    printf("[");
    while(curr != NULL){
        printf("%d", *(int*)curr->val);
        if(curr->next != NULL){
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]\n");
}

queue_t* queue_create(size_t type_size, free_t free){
        queue_t* new = calloc(1, sizeof(queue_t));
        new->size = 0;
        new->type_size = type_size;
        new->free_func = free;
        return new;
}

void queue_enqueue(queue_t* queue, void* val){
    queue_node_t* new = calloc(1, sizeof(queue_node_t));
    new->type_size = queue->type_size;
    new->val = val;

    if(queue->size == 0){
        queue->head = new;
        queue->tail = new;
        queue->size++;
        queue->stats.enqueues++;
        // print_queue(queue);
        return;
    }

    queue->head->prev = new;
    new->next = queue->head;
    queue->head = new;
    queue->size++;
    queue->stats.enqueues++;
    // print_queue(queue);
}

void* queue_dequeue(queue_t* queue){
    if(queue->size == 0){
        return NULL;
    }

    // print_queue(queue);
    
    if (queue->size == 1){
        void* val = queue->tail->val;
        free(queue->tail);
        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
        queue->stats.dequeues++;
        return val;
    }

    if (queue->size == 2){
        void* val = queue->tail->val;
        queue_node_t* temp = queue->tail;
        queue->tail = queue->head;
        queue->tail->next = NULL;
        free(temp);
        queue->size--;
        queue->stats.dequeues++;
        return val;
    }

    void* val = queue->tail->val;
    queue_node_t* temp = queue->tail;
    queue->tail = queue->tail->prev;
    queue->tail->next = NULL;
    free(temp);
    queue->size--;
    queue->stats.dequeues++;
    return val;
}

void* queue_peek(queue_t* queue){
    if(queue->size == 0){
        return NULL;
    }
    queue->stats.peeks++;
    return queue->tail->val;
}

void queue_free(queue_t* queue){
    queue_node_t* curr = queue->head;
    while(curr != NULL){
        queue_node_t* temp = curr;
        curr = curr->next;
        free(temp->val);
        free(temp);
    }
    free(queue);
}

void queue_print_stats(queue_t* queue){
    printf("enqueues: %lu\n", queue->stats.enqueues);
    printf("Peeks: %lu\n", queue->stats.peeks);
    printf("dequeues: %lu\n", queue->stats.dequeues);
}