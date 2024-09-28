// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

void print_stack(stack_t* stack){
    stack_node_t* curr = stack->head;
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

stack_t* stack_create(size_t type_size, free_t free){
        stack_t* new = calloc(1, sizeof(stack_t));
        new->size = 0;
        new->type_size = type_size;
        new->free_func = free;
        return new;
}

void stack_push(stack_t* stack, void* val){
    stack_node_t* new = calloc(1, sizeof(stack_node_t));
    new->val = val, stack->type_size;
    new->type_size = stack->type_size;
    new->next = stack->head;
    stack->head = new;
    stack->size++;
    stack->stats.pushes++;
    // print_stack(stack);
}

void* stack_pop(stack_t* stack){
    if(stack->size == 0){
        return NULL;
    }

    // print_stack(stack);

    stack_node_t* temp = stack->head;
    stack->head = stack->head->next;
    stack->size--;
    void* val = temp->val;
    free(temp);

    stack->stats.pops++;
    return val;
}

void* stack_peek(stack_t* stack){
    if(stack->size == 0){
        return NULL;
    }
    
    stack->stats.peeks++;
    return stack->head->val;
}

void stack_free(stack_t* stack){
    stack_node_t* curr = stack->head;
    while(curr != NULL){
        stack_node_t* temp = curr;
        curr = curr->next;
        if(stack->free_func != NULL){
            stack->free_func(temp->val);
        }else{
            free(temp->val);
        }
        free(temp);
    }
    free(stack);
}

void stack_print_stats(stack_t* stack){
    printf("Pushes: %lu\n", stack->stats.pushes);
    printf("Peeks: %lu\n", stack->stats.peeks);
    printf("Pops: %lu\n", stack->stats.pops);
}