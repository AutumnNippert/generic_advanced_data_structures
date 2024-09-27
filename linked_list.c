// create a typedef for an equals function pointer

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "linked_list.h"

typedef struct linked_list_stats{
    size_t adds;
    size_t removes;
    size_t frees;
}linked_list_stats_t;

linked_list_stats_t stats = {0, 0, 0};

linked_list_t* linked_list_create(size_t type_size, equals_t equals, type_check_t type_check, free_t free){
    linked_list_t* new = calloc(1, sizeof(linked_list_t));
    new->size = 0;
    new->type_size = type_size;
    new->equals_func = equals;
    new->type_check_func = type_check;
    new->free_func = free;
    return new;
}

void linked_list_add_sorted(linked_list_t* linked_list, void* val, compare_t compare){
    // check if compare is null
    assert(compare);

    linked_list_node_t* new = calloc(1, sizeof(linked_list_node_t));
    new->val = val;
    new->type_size = linked_list->type_size;
    new->next = NULL;
    new->prev = NULL;

    if(linked_list->size == 0){
        linked_list->head = new;
        linked_list->tail = new;
        linked_list->size++;
        return;
    }

    linked_list_node_t* curr = linked_list->head;
    while(curr != NULL){
        if(compare(curr->val, val) > 0){
            if(curr->prev != NULL){
                curr->prev->next = new;
                new->prev = curr->prev;
            }
            new->next = curr;
            curr->prev = new;
            if(curr == linked_list->head){
                linked_list->head = new;
            }
            linked_list->size++;
            return;
        }
        curr = curr->next;
    }
    linked_list->tail->next = new;
    new->prev = linked_list->tail;
    linked_list->tail = new;
    linked_list->size++;
}

void linked_list_add(linked_list_t* linked_list, void* val){

    stats.adds++;

    linked_list_node_t* new = calloc(1, sizeof(linked_list_node_t));
    new->val = val;
    new->type_size = linked_list->type_size;
    new->next = NULL;
    new->prev = NULL;

    if(linked_list->size == 0){
        linked_list->head = new;
        linked_list->tail = new;
        linked_list->size++;
        return;
    }

    linked_list->tail->next = new;
    new->prev = linked_list->tail;
    linked_list->tail = new;
    linked_list->size++;
}

int linked_list_add_if_not_contains(linked_list_t* linked_list, void* val){
    if(linked_list_contains(linked_list, val)){
        return 0; // fail
    }
    linked_list_add(linked_list, val);
    return 1; // success
}

void* linked_list_get_index(linked_list_t* linked_list, size_t index){
    if(index >= linked_list->size){
        return NULL;
    }
    linked_list_node_t* curr = linked_list->head;
    for(size_t i = 0; i < index; i++){
        curr = curr->next;
    }
    return curr->val;
}

void* linked_list_get(linked_list_t* linked_list, void* val){
    linked_list_node_t* curr = linked_list->head;
    while(curr != NULL){
        if(linked_list->equals_func(curr->val, val)){
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

void linked_list_free(linked_list_t* linked_list){
    // check if free is null
    free_t free_func = linked_list->free_func;
    if(free_func == NULL){ // generic free
        linked_list_node_t* curr = linked_list->head;
        while(curr != NULL){
            linked_list_node_t* next = curr->next;
            free(curr);
            curr = next;
            stats.frees++;
        }
        free(linked_list);
        return;
    }
    else{
        linked_list_node_t* curr = linked_list->head;
        while(curr != NULL){
            linked_list_node_t* next = curr->next;
            free_func(curr->val);
            free(curr);
            stats.frees++;
            curr = next;
        }
        free(linked_list);
        return;
    }
}

bool linked_list_contains(linked_list_t* linked_list, void* val){
    linked_list_node_t* curr = linked_list->head;
    while(curr != NULL){
        if(linked_list->equals_func(curr->val, val)){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void linked_list_remove(linked_list_t* linked_list, void* val){
    printf("Removing\n");
    // check if type_check is null
    if(linked_list->type_check_func != NULL){
        assert(linked_list->type_check_func(val) == 0);
    }

    // make sure equals is not null
    assert(linked_list->equals_func != NULL);

    linked_list_node_t* curr = linked_list->head;

    while(curr != NULL){
        if(linked_list->equals_func(curr->val, val) == 0){
            if(linked_list->size == 1){
                linked_list->head = NULL;
                linked_list->tail = NULL;
                linked_list->size--;
            }

            if(curr == linked_list->head){
                linked_list->head = curr->next;
            }

            if(curr == linked_list->tail){
                linked_list->tail = curr->prev;
            }

            if(curr->prev != NULL){
                curr->prev->next = curr->next;
            }
            if(curr->next != NULL){
                curr->next->prev = curr->prev;
            }
            linked_list->size--;

            free(curr);
            stats.frees++;
            stats.removes++;
            return;
        }
    }
}

void linked_list_sort(linked_list_t* linked_list, compare_t compare){
    // check if compare is null
    if(compare == NULL){
        return;
    }

    linked_list_node_t* curr = linked_list->head;
    while(curr != NULL){
        linked_list_node_t* next = curr->next;
        while(next != NULL){
            if(compare(curr->val, next->val) > 0){
                void* temp = curr->val;
                curr->val = next->val;
                next->val = temp;
            }
            next = next->next;
        }
        curr = curr->next;
    }
}

void print_stats(){
    printf("Adds: %lu\n", stats.adds);
    printf("Removes: %lu\n", stats.removes);
    printf("Frees: %lu\n", stats.frees);
}