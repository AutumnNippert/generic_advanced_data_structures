#include "prim_functions.h"

///////////////////////////////////////////////////////////////////////////
//////////////////////////// COMPARE FUNCTIONS ////////////////////////////
///////////////////////////////////////////////////////////////////////////

// all numbers and chars can be compared with the same function by casting to the largest type
int compare_alphanum(void* a, void* b){
    long long a_long = *(long long*)a;
    long long b_long = *(long long*)b;

    if (a_long == b_long){
        return 0;
    }
    if(a_long < b_long){
        return -1;
    }
    return 1;
}

// floats are different though
int compare_float(void* a, void* b){
    float a_float = *(float*)a;
    float b_float = *(float*)b;

    if (a_float == b_float){
        return 0;
    }
    if(a_float < b_float){
        return -1;
    }
    return 1;
}

// doubles are also different
int compare_double(void* a, void* b){
    double a_double = *(double*)a;
    double b_double = *(double*)b;

    if (a_double == b_double){
        return 0;
    }
    if(a_double < b_double){
        return -1;
    }
    return 1;
}

int compare_string(void* a, void* b){
    return strcmp((char*)a, (char*)b);
}