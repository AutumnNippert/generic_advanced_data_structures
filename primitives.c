#include "primitives.h"

///////////////////////////////////////////////////////////////////////////
//////////////////////////// COMPARE FUNCTIONS ////////////////////////////
///////////////////////////////////////////////////////////////////////////

int compare_int(void* a, void* b){
    return *(int*)a - *(int*)b;
}

int compare_unsigned_int(void* a, void* b){
    unsigned int a_int = *(unsigned int*)a;
    unsigned int b_int = *(unsigned int*)b;

    if(a_int == b_int)
        return 0;
    return 1;
}

int min_compare_int(void* a, void* b){
    return *(int*)b - *(int*)a;
}

/**
 * @brief Compares two floats
 * 
 * @param a float a
 * @param b float b
 * @return int 0 if equal, -1 if a < b, 1 if a > b
 */
int compare_float(void* a, void* b){
    return *(float*)a - *(float*)b;
}

// doubles are also different
int compare_double(void* a, void* b){
    return *(double*)a - *(double*)b;

}

int compare_string(void* a, void* b){
    return strcmp((char*)a, (char*)b);
}