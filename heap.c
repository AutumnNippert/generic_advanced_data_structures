/*
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
*/

#include "heap.h"

heap_t* heap_create(size_t type_size, compare_t compare, free_t free){
    heap_t* heap = malloc(sizeof(heap_t));
    heap->type_size = type_size;
    heap->compare = compare;
    heap->free = free;
    heap->arr = dsa_create(type_size, compare, free);
    heap->size = 0;
    heap->capacity = 0;
    return heap;
}

static size_t get_left_child(size_t index){
    return 2 * index + 1;
}

static size_t get_right_child(size_t index){
    return 2 * index + 2;
}

static size_t get_parent(size_t index){
    return (index - 1) / 2;
}

static void swap(heap_t* heap, size_t index1, size_t index2){
    void* temp = dsa_get(heap->arr, index1);
    dsa_set(heap->arr, dsa_get(heap->arr, index2), index1);
    dsa_set(heap->arr, temp, index2);
}

static void increase_key(heap_t* heap, size_t index, void* val){
    dsa_set(heap->arr, val, index);
    while (index > 0 && heap->compare(dsa_get(heap->arr, get_parent(index)), dsa_get(heap->arr, index)) < 0){
        swap(heap, index, get_parent(index));
        index = get_parent(index);
    }
}

static void decrease_key(heap_t* heap, size_t index, void* val){
    dsa_set(heap->arr, val, index);
    while (get_left_child(index) < heap->size){
        size_t largest = index;
        size_t left = get_left_child(index);
        size_t right = get_right_child(index);
        if (left < heap->size && heap->compare(dsa_get(heap->arr, left), dsa_get(heap->arr, largest)) > 0){
            largest = left;
        }
        if (right < heap->size && heap->compare(dsa_get(heap->arr, right), dsa_get(heap->arr, largest)) > 0){
            largest = right;
        }
        if (largest == index){
            break;
        }
        swap(heap, index, largest);
        index = largest;
    }
}

heap_t* heapify(size_t type_size, compare_t compare, free_t free, dsa_t* arr, size_t size){
    /*
        Check if the left child exists.
        If the left child exists and is greater than the current largest node, mark it as largest.
        Check if the right child exists.
        If the right child exists and is greater than the current largest node, mark it as largest
        If the largest node is not the root node, swap the root node with the largest node using the swap function.
        Apply heapify operation to the affected subtree.
     */
    heap_t* heap = malloc(sizeof(heap_t));
    heap->type_size = type_size;
    heap->compare = compare;
    heap->free = free;
    heap->arr = arr;
    heap->size = size;
    heap->capacity = size;
    for (int i = size / 2; i >= 0; i--){
        size_t largest = i;
        size_t left = get_left_child(i);
        size_t right = get_right_child(i);
        if (left < size && compare(dsa_get(arr, left), dsa_get(arr, largest)) > 0){
            largest = left;
        }
        if (right < size && compare(dsa_get(arr, right), dsa_get(arr, largest)) > 0){
            largest = right;
        }
        if (largest != i){
            swap(heap, i, largest);
        }
    }
    return heap;
}

void heap_push(heap_t* heap, void* val){
    if (heap->size == heap->capacity){
        dsa_append(heap->arr, val);
        heap->capacity++;
    } else{
        dsa_set(heap->arr, val, heap->size);
    }
    increase_key(heap, heap->size, val);
    heap->size++;
}

void* heap_peek(heap_t* heap){
    if (heap->size == 0){
        return NULL;
    }
    return dsa_get(heap->arr, 0);
}

void* heap_pop(heap_t* heap){
    if (heap->size == 0){
        return NULL;
    }
    void* max = dsa_get(heap->arr, 0);
    dsa_set(heap->arr, dsa_get(heap->arr, heap->size - 1), 0);
    heap->size--;
    decrease_key(heap, 0, dsa_get(heap->arr, 0));
    return max;
}

void heap_free(heap_t* heap){
    if (heap->free != NULL){
        for (int i = 0; i < heap->size; i++){
            heap->free(dsa_get(heap->arr, i));
        }
    }
    dsa_free(heap->arr);
    free(heap);
}

void heap_print(heap_t* heap){
    dsa_print(heap->arr);
}