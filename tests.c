#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linked_list.h"
#include "stack.h"
#include "heap.h"
// void linked_list_test(){
//         // create a compare function for int
//     int compare_int(void* a, void* b){
//         return *(int*)a == *(int*)b;
//     }

//     void free_int(void* a){
//         free(a);
//     }

//     // create a linked_list
//     linked_list_t* linked_list = linked_list_create(sizeof(int), compare_int, NULL, free_int);
//     int a = 1;
//     linked_list_add(linked_list, (void*)&a);

//     // print the linked_list
//     for(size_t i = 0; i < linked_list->size; i++){
//         printf("%d\n", *(int*)linked_list_get_index(linked_list, i));
//     }
    
//     int b = 2;
//     linked_list_add(linked_list, (void*)&b);

//     int c = 3;
//     linked_list_add(linked_list, (void*)&c);

//     // get the value at index 1
//     int* val = linked_list_get_index(linked_list, 1);
//     printf("Value at index 1: %d\n", *val);

//     // remove the value at index 1
//     int d = 2;
//     linked_list_remove(linked_list, (void*)&d);

//     // print the linked_list
//     for(size_t i = 0; i < linked_list->size; i++){
//         printf("%d\n", *(int*)linked_list_get_index(linked_list, i));
//     }

//     linked_list_free(linked_list);
// }

void stack_test(){
    stack_t *stack = stack_create(sizeof(int), NULL);
    //add 1 to the stack
    stack_push(stack, (void*)&(int){1});
    assert(*(int*)stack_peek(stack) == 1);
    assert(*(int*)stack_pop(stack) == 1);
    assert(stack_peek(stack) == NULL);

    //add more than one element to the stack
    int* arr = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++){
        arr[i] = i;
    }
    for (int i = 0; i < 10; i++){
        stack_push(stack, (void*)&arr[i]);
    }

    //pop all elements from the stack
    for (int i = 9; i >= 0; i--){
        assert(*(int*)stack_peek(stack) == i);
        assert(*(int*)stack_pop(stack) == i);
    }

    free(arr);

    stack_print_stats(stack);
    stack_free(stack);
}

void min_heap_test(){
    int min_compre_int(void* a, void* b){
        return *(int*)a - *(int*)b;
    }

    void free_int(void* a){
        free(a);
    }

    heap_t* heap = heap_create(sizeof(int), min_compre_int, free_int);
    int arr[10] = {5, 3, 7, 1, 2, 9, 4, 6, 8, 0};
    for (int i = 0; i < 10; i++){ // O(nlog(n))
        heap_push(heap, (void*)&arr[i]);
    }
    for (int i = 0; i < 10; i++){ // O(nlog(n))
        printf("%d\n", *(int*)heap_pop(heap));
    }
    heap_free(heap);
}

int main(){
    // linked_list_test();
    stack_test();
    min_heap_test();
    return 0;
}