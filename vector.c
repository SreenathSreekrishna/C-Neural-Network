#include <stdlib.h>
#ifndef __matrix__
#include "matrix.c"
#endif
#include "neuron.c"

typedef struct Vector {
    float *arr;
    int length;
} Vector;

Vector new_vector(int length){
    Vector vector;
    float *vecarr = malloc((length+1)*sizeof(float));
    for (int i = 0; i<length; i++){
        vecarr[i] = getRand();
    }
    vecarr[length] = 0;
    vector.arr = vecarr;
    vector.length = length;
    return vector;
}

float sum(Vector v){
    float _sum = 0;
    for (int i = 0; i<v.length; i++){
        _sum+=v.arr[i];
    }
    return _sum;
}

Vector vMultiply(Vector v1, Vector v2){
    Vector product = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        float prod = v1.arr[i] * v2.arr[i];
        product.arr[i] = prod;
    }
    return product;
}

float vDot(Vector v1, Vector v2){
    Vector product = vMultiply(v1,v2);
    float dot = sum(product);
    free(product.arr);
    return dot;
}

Vector vSub(Vector v1, Vector v2){
    Vector result = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        result.arr[i] = v1.arr[i]-v2.arr[i];
    }
    return result;
}

Vector vSquare(Vector v){
    Vector result = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        result.arr[i] = v.arr[i]*v.arr[i];
    }
    return result;
}