#include <inttypes.h>
#include <stdio.h>

typedef int (*compare_t)(void*, void*);
typedef void (*free_t)(void*);

int compare_alphanum(void* a, void* b);
int compare_float(void* a, void* b);
int compare_double(void* a, void* b);

