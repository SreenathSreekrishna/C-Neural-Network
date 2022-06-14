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
Vector new_vector_zeroes(int length){
    Vector vector;
    float *vecarr = malloc((length+1)*sizeof(float));
    for (int i = 0; i<length; i++){
        vecarr[i] = 0.0;
    }
    vecarr[length] = 0;
    vector.arr = vecarr;
    vector.length = length;
    return vector;
}

Vector vCopy(Vector v){
    Vector end = new_vector_zeroes(v.length);
    for (int i = 0; i<v.length; i++){
        end.arr[i] = v.arr[i];
    }
    return end;
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

Vector vMultiplyConst(Vector v, float n){
    Vector product = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        product.arr[i] = v.arr[i] * n;
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

Vector vSubConst(Vector v, float n){
    Vector result = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        result.arr[i] = v.arr[i]-n;
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

Vector vDivide(Vector v1, Vector v2){
    Vector division = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        division.arr[i] = v1.arr[i] / v2.arr[i];
    }
    return division;
}

Vector vDivideConst(Vector v, float n){
    Vector division = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        division.arr[i] = v.arr[i] / n;
    }
    return division;
}

void printVector(Vector v){
    for (int i = 0; i<v.length; i++){
        printf("%f ", v.arr[i]);
    }
    printf("\n");
}

float max(Vector v){
    float _max = -32768.0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]>_max){
            _max = v.arr[i];
        }
    }
    return _max;
}

float min(Vector v){
    float _min = 32768.0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]<_min){
            _min = v.arr[i];
        }
    }
    return _min;
}

float argMax(Vector v){
    float _max = -32768.0;
    int index = 0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]>_max){
            _max = v.arr[i];
            index = i;
        }
    }
    return index;
}

float argMin(Vector v){
    float _min = 32768.0;
    int index = 0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]<_min){
            _min = v.arr[i];
            index = i;
        }
    }
    return index;
}

void vUpdateSum(Vector *v, Vector vals){
    for (int i = 0; i<vals.length; i++){
        v->arr[i] = v->arr[i] + vals.arr[i];
    }
}