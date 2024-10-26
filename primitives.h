#include <stdio.h>
#include <string.h>

#pragma once // this takes care of the multiple inclusion problem and making include guards

typedef struct char_wrapper{ char val; } char_t;
typedef struct unsigned_char_wrapper{ unsigned char val; } unsigned_char_t;
typedef struct int_wrapper{ int val; } int_t;
typedef struct unsigned_int_wrapper{ unsigned int val; } unsigned_int_t;
typedef struct long_wrapper{ long val; } long_t;
typedef struct unsigned_long_wrapper{ unsigned long val; } unsigned_long_t;
typedef struct long_long_wrapper{ long long val; } long_long_t;
typedef struct unsigned_long_long_wrapper{ unsigned long long val; } unsigned_long_long_t;
typedef struct float_wrapper{ float val; } float_t;
typedef struct double_wrapper{ double val; } double_t;

typedef int (*compare_t)(void*, void*);
typedef void (*free_t)(void*);

int compare_int(void* a, void* b);
int compare_unsigned_int(void* a, void* b);
int min_compare_int(void* a, void* b);
int compare_float(void* a, void* b);
int compare_double(void* a, void* b);
