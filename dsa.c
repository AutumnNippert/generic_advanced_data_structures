#include "dsa.h"

/**
 * @brief Creates a new dsa_t struct
 * @param type_size The size of the type that will be stored in the dsa
 * @param compare The compare function for the type that will be stored in the dsa
 * @param free The free function for the type that will be stored in the dsa
 * @return The new dsa_t struct
 */
dsa_t* dsa_create(size_t type_size, compare_t compare, free_t free){
    dsa_t* new = calloc(1, sizeof(dsa_t));
    new->size = 0;
    new->capacity = 1;
    new->type_size = type_size;
    new->compare_func = compare;
    new->free_func = free;
    new->arr = calloc(1, sizeof(void*));
    return new;
}

dsa_t* dsa_from_array(size_t type_size, compare_t compare, free_t free, void* arr, size_t arr_size){
    dsa_t* new = dsa_create(type_size, compare, free);
    for(size_t i = 0; i < arr_size; i++){
        dsa_append(new, arr + i * type_size);
    }
    return new;
}

/**
 * @brief Doubles the size of the dsa
 * @param dsa The dsa to double the size of
 * @return The dsa with the doubled size
 */
static dsa_t* dsa_double_size(dsa_t* dsa){
    dsa->capacity *= 2;
    dsa->arr = realloc(dsa->arr, dsa->capacity * sizeof(void*));
    return dsa;
}

/**
 * @brief Checks if the dsa is full
 * @param dsa The dsa to check
 * @return 1 if the dsa is full, 0 otherwise
 */
static int dsa_is_full(dsa_t* dsa){
    return dsa->size == dsa->capacity;
}

/**
 * @brief Gets the value at the given index
 * @param data_structure The dsa to get the value from
 * @param index The index to get the value from
 * @return The value at the given index
 */
void* dsa_get(dsa_t* data_structure, size_t index){
    return data_structure->arr[index];
}

/**
 * @brief Sets the value at the given index
 * @param data_structure The dsa to set the value in
 * @param val The value to set
 * @param index The index to set the value at
 */
void dsa_set(dsa_t* data_structure, void* val, size_t index){
    if(index >= data_structure->size){
        return; // ignore it
    }
    data_structure->arr[index] = val;
}

/**
 * @brief Inserts a value at the given index
 * @param dsa The dsa to insert the value into
 * @param val The value to insert
 * @param index The index to insert the value at
 */
void dsa_insert(dsa_t* dsa, void* val, size_t index){
    if(dsa_is_full(dsa)){
        dsa = dsa_double_size(dsa);
    }
    for(size_t i = dsa->size; i > index; i--){
        dsa->arr[i] = dsa->arr[i - 1];
    }
    dsa->arr[index] = val;
    dsa->size++;
}

/**
 * @brief Appends a value to the dsa
 * @param dsa The dsa to append the value to
 * @param val The value to append
 */
void dsa_append(dsa_t* dsa, void* val){
    if(dsa_is_full(dsa)){
        dsa = dsa_double_size(dsa);
    }
    dsa->arr[dsa->size] = val;
    dsa->size++;
}

/**
 * @brief Removes the value at the given index
 * @param dsa The dsa to remove the value from
 * @param index The index to remove the value from
 * @return The value that was removed
 */
void* dsa_remove(dsa_t* dsa, size_t index){
    void* val = dsa->arr[index];
    for(size_t i = index; i < dsa->size - 1; i++){
        dsa->arr[i] = dsa->arr[i + 1];
    }
    dsa->size--;
    return val;
}

/**
 * @brief Frees the dsa
 * @param dsa The dsa to free
 */
void dsa_free(dsa_t* dsa){
    if (dsa->free_func == NULL){
        free(dsa->arr);
        free(dsa);
        return;
    }
    for(size_t i = 0; i < dsa->size; i++){
        dsa->free_func(dsa->arr[i]);
    }
    free(dsa->arr);
    free(dsa);
}

/**
 * @brief Prints the dsa
 * @param dsa The dsa to print
 */
void dsa_print(dsa_t* dsa){
    printf("[");
    for(size_t i = 0; i < dsa->size; i++){
        printf("%d", *(int*)dsa->arr[i]);
        if(i != dsa->size - 1){
            printf(", ");
        }
    }
    printf("]\n");
}