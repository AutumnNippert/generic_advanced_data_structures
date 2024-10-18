#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "linked_list.h"
#include "stack.h"
#include "queue.h"
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



int* stack_test_int(){
    int* errs = {0};
    int err_index = 0;

    stack_t *stack = stack_create(sizeof(int), NULL);
    //add 1 to the stack
    stack_push(stack, (void*)&(int){1});
    if(!(*(int*)stack_peek(stack) == 1)){
        errs[err_index++] = 1;
    }
    if(!(*(int*)stack_pop(stack) == 1)){
        errs[err_index++] = 2;
    }
    if(!(stack_peek(stack) == NULL)){
        errs[err_index++] = 3;
    }

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
        if(!(*(int*)stack_peek(stack) == i)){
            errs[err_index++] = 4;
        }
        if(!(*(int*)stack_pop(stack) == i)){
            errs[err_index++] = 5;
        }
    }

    free(arr);
    // stack_print_stats(stack);
    stack_free(stack);

    return errs;
}

int* stack_test_string(){
    int* errs = {0};
    int err_index = 0;

    stack_t *stack = stack_create(sizeof(char*), free);
    //add 1 to the stack
    stack_push(stack, (void*)"hello");
    if(!(strcmp((char*)stack_peek(stack), "hello") == 0)){
        errs[err_index++] = 1;
    }
    if(!(strcmp((char*)stack_pop(stack), "hello") == 0)){
        errs[err_index++] = 2;
    }
    if(!(stack_peek(stack) == NULL)){
        errs[err_index++] = 3;
    }

    //add more than one element to the stack
    char* arr[10] = {"hello", "world", "this", "is", "a", "test", "of", "the", "stack", "function"};
    for (int i = 0; i < 10; i++){
        stack_push(stack, (void*)arr[i]);
    }

    //pop all elements from the stack
    for (int i = 9; i >= 0; i--){
        if(!(strcmp((char*)stack_peek(stack), arr[i]) == 0)){
            errs[err_index++] = 4;
        }
        if(!(strcmp((char*)stack_pop(stack), arr[i]) == 0)){
            errs[err_index++] = 5;
        }
    }

    // stack_print_stats(stack);
    stack_free(stack);

    return errs;
}

int* queue_test_int(){
    int* errs = {0};
    int err_index = 0;

    queue_t *queue = queue_create(sizeof(int), NULL);
    //add 1 to the queue
    queue_enqueue(queue, (void*)&(int){1});
    if (!(*(int*)queue_peek(queue) == 1)){
        errs[err_index++] = 1;
    }
    if (!(*(int*)queue_dequeue(queue) == 1)){
        errs[err_index++] = 2;
    }
    if (!(queue_peek(queue) == NULL)){
        errs[err_index++] = 3;
    }

    //add more than one element to the queue
    int* arr = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++){
        arr[i] = i;
    }
    for (int i = 0; i < 10; i++){
        queue_enqueue(queue, (void*)&arr[i]);
    }

    //pop all elements from the queue
    for (int i = 0; i < 10; i++){
        if (!(*(int*)queue_peek(queue) == i)){
            errs[err_index++] = 4;
        }
        if (!(*(int*)queue_dequeue(queue) == i)){
            errs[err_index++] = 5;
        }
    }

    free(arr);
    // queue_print_stats(queue);
    queue_free(queue);

    return errs;
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
    int* stack_int_errs = stack_test_int();
    int* stack_string_errs = stack_test_string();
    int* queue_int_errs = queue_test_int();

    printf("Stack int errors: ");
    for (int i = 0; i < 100; i++){
        if (stack_int_errs[i] != 0){
            printf("%d, ", stack_int_errs[i]);
        }
    }
    printf("\n");

    printf("Stack string errors: ");
    for (int i = 0; i < 100; i++){
        if (stack_string_errs[i] != 0){
            printf("%d, ", stack_string_errs[i]);
        }
    }
    printf("\n");

    printf("Queue int errors: ");
    for (int i = 0; i < 100; i++){
        if (queue_int_errs[i] != 0){
            printf("%d, ", queue_int_errs[i]);
        }
    }
    printf("\n");
    min_heap_test();
    return 0;
}