/**
 * @file dsa.h
 * @brief This file contains the declarations for the data structures and algorithms library.
 * @author Autumn Nippert
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "primitives.h"

#pragma once

typedef struct dsa{
    size_t size;
    size_t capacity;
    size_t type_size;
    compare_t compare_func;
    free_t free_func;
    void** arr;
} dsa_t;

dsa_t* dsa_create(size_t type_size, compare_t compare, free_t free);
dsa_t* dsa_from_array(size_t type_size, compare_t compare, free_t free, void* arr, size_t arr_size);
void* dsa_get(dsa_t* data_structure, size_t index);
void dsa_set(dsa_t* data_structure, void* val, size_t index);
void dsa_insert(dsa_t* dsa, void* val, size_t index);
void dsa_append(dsa_t* dsa, void* val);
void* dsa_remove(dsa_t* dsa, size_t index);
void dsa_free(dsa_t* dsa);

void dsa_print(dsa_t* dsa);