#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "primitives.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"
#include "dsa.h"

void primitive_comparitor_test(){
    int failed = 0;

    void* ia = (void*)&(int){1};
    void* ib = (void*)&(int){2};
    void* ic = (void*)&(int){1};

    void* fa = (void*)&(float){1.0};
    void* fb = (void*)&(float){2.0};
    void* fc = (void*)&(float){1.0};

    void* da = (void*)&(double){1.0};
    void* db = (void*)&(double){2.0};
    void* dc = (void*)&(double){1.0};
    
    if (compare_int(&ia, &ib) < 0){
        printf("compare_int_1 failed\n");
        failed = 1;
    }
    if (compare_int(&ia, &ic) != 0){
        printf("compare_int_2 failed\n");
        failed = 1;

    }
    if (compare_int(&ib, &ia) >= 0){
        printf("compare_int_3 failed\n");
        failed = 1;
    }

    if (compare_float(&fa, &fb) <= 0){
        printf("compare_float_1 failed\n");
        failed = 1;
    }
    if (compare_float(&fa, &fc) != 0){
        printf("compare_float_2 failed\n");
        failed = 1;
    }
    if (compare_float(&fb, &fa) >= 0){
        printf("compare_float_3 failed\n");
        failed = 1;
    }

    if (compare_double(&da, &db) <= 0){
        printf("compare_double_1 failed\n");
        failed = 1;
    }
    if (compare_double(&da, &dc) != 0){
        printf("compare_double_2 failed\n");
        failed = 1;
    }
    if (compare_double(&db, &da) >= 0){
        printf("compare_double_3 failed\n");
        failed = 1;
    }
    if (!failed){
        printf("primitive_comparitor_test passed\n");
    } else{
        printf("primitive_comparitor_test failed\n");
    }
}

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

void dsa_test_int(){
    int failed = 0;

    dsa_t *dsa = dsa_create(sizeof(int), compare_int, free);
    //add 1 to the dsa
    dsa_append(dsa, (void*)&(int){1});
    if (!(*(int*)dsa_get(dsa, 0) == 1)){
        printf("dsa_test_int: 1\n");
        failed = 1;
    }
    if (!(*(int*)dsa_remove(dsa, 0) == 1)){
        printf("dsa_test_int: 2\n");
        failed = 1;
    }

    //add more than one element to the dsa
    int* arr = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++){
        arr[i] = i;
    }
    for (int i = 0; i < 10; i++){
        dsa_append(dsa, (void*)&arr[i]);
    }

    //pop all elements from the dsa
    for (int i = 0; i < 10; i++){
        if (!(*(int*)dsa_get(dsa, 0) == i)){
            printf("dsa_test_int: 3\n");
            failed = 1;
            break;
        }
        if (!(*(int*)dsa_remove(dsa, 0) == i)){
            printf("dsa_test_int: 4\n");
            failed = 1;
            break;
        }
    }

    free(arr);
    dsa_free(dsa);

    //test from_array
    int_t* arr2[10];
    for (int i = 0; i < 10; i++){
        arr2[i] = malloc(sizeof(int_t));
        arr2[i]->val = i;
    }
    dsa_t* dsa2 = dsa_from_array(sizeof(int_t), compare_int, NULL, arr2, 10);
    for (int i = 0; i < 10; i++){
        if (!(*(int*)dsa_get(dsa2, i) == i)){
            printf("dsa_test_int: 5\n");
            failed = 1;
            break;
        }
    }
    dsa_free(dsa2);
    for (int i = 0; i < 10; i++){
        free(arr2[i]);
    }
    if (!failed){
        printf("dsa_test_int passed\n");
    } else{
        printf("dsa_test_int failed\n");
    }
}

void dsa_usability_test(){
    dsa_t* dsa = dsa_create(sizeof(int), compare_int, NULL);
    dsa_append(dsa, (void*)&(int){1});
    dsa_append(dsa, (void*)&(int){2});

    dsa_print(dsa);

    dsa_set(dsa, (void*)&(int){3}, 0);
    dsa_print(dsa);

    dsa_set(dsa, (void*)&(int){4}, 12); // will be ignored as index is out of bounds
    dsa_print(dsa);

    dsa_insert(dsa, (void*)&(int){4}, 0);
    dsa_print(dsa);

    dsa_insert(dsa, (void*)&(int){4}, 1);
    dsa_print(dsa);

    dsa_remove(dsa, 0);
    dsa_print(dsa);

    dsa_free(dsa);

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    dsa_t* dsa_arr = dsa_from_array(sizeof(int), compare_int, NULL, arr, 10);
    dsa_print(dsa_arr);

    dsa_insert(dsa_arr, (void*)&(int){10}, 5);
    dsa_append(dsa_arr, (void*)&(int){11});
    dsa_print(dsa_arr);

    dsa_free(dsa_arr);

    printf("dsa_usability_test passed\n");
}

void min_heap_test(){
    heap_t* heap = heap_create(sizeof(int), min_compare_int, NULL);
    int arr[11] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 12};
    for (int i = 0; i < 11; i++){ // O(nlog(n))
        heap_push(heap, (void*)&arr[i]);
    }
    heap_print(heap);
    for (int i = 0; i < 11; i++){ // O(nlog(n))
        printf("%d\n", *(int*)heap_pop(heap));
    }
    heap_free(heap);
    printf("min_heap_test passed\n");
}

int main(){
    // linked_list_test();
    primitive_comparitor_test();
    int* stack_int_errs = stack_test_int();
    int* stack_string_errs = stack_test_string();
    int* queue_int_errs = queue_test_int();

    dsa_test_int();
    dsa_usability_test();
    min_heap_test();
    return 0;
}