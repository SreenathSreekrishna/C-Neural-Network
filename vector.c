#include <stdlib.h>
#ifndef __matrix__
#include "matrix.c"
#endif
#include "neuron.c"

typedef struct Vector {
    double *arr;
    int length;
} Vector;

Vector new_vector(int length){
    Vector vector;
    double *vecarr = malloc((length+1)*sizeof(double));
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
    double *vecarr = malloc((length+1)*sizeof(double));
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

double sum(Vector v){
    double _sum = 0;
    for (int i = 0; i<v.length; i++){
        _sum+=v.arr[i];
    }
    return _sum;
}

double sumF(Vector *v){
    double _sum = sum(*v);
    free(v->arr);
    return _sum;
}

Vector vMultiply(Vector v1, Vector v2){
    Vector product = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        double prod = v1.arr[i] * v2.arr[i];
        product.arr[i] = prod;
    }
    return product;
}

Vector vMultiplyF(Vector *v1, Vector *v2){
    Vector product = vMultiply(*v1, *v2);
    free(v1->arr);
    free(v2->arr);
    return product;
}

Vector vMultiplyConst(Vector v, double n){
    Vector product = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        product.arr[i] = v.arr[i] * n;
    }
    return product;
}

Vector vMultiplyConstF(Vector *v, double n){
    Vector product = vMultiplyConst(*v, n);
    free(v->arr);
    return product;
}

double vDot(Vector v1, Vector v2){
    Vector product = vMultiply(v1,v2);
    double dot = sum(product);
    free(product.arr);
    return dot;
}

double vDotF(Vector *v1, Vector *v2){
    double dot = vDot(*v1, *v2);
    free(v1->arr);
    free(v2->arr);
    return dot;
}

Vector vSub(Vector v1, Vector v2){
    Vector result = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        result.arr[i] = v1.arr[i]-v2.arr[i];
    }
    return result;
}

Vector vSubF(Vector *v1, Vector *v2){
    Vector result = vSub(*v1, *v2);
    free(v1->arr);
    free(v2->arr);
    return result;
}

Vector vSubConst(Vector v, double n){
    Vector result = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        result.arr[i] = v.arr[i]-n;
    }
    return result;
}

Vector vSubConstF(Vector *v, double n){
    Vector result = vSubConst(*v, n);
    free(v->arr);
    return result;
}

Vector vSquare(Vector v){
    Vector result = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        result.arr[i] = v.arr[i]*v.arr[i];
    }
    return result;
}

Vector vSquareF(Vector *v){
    Vector result = vSquare(*v);
    free(v->arr);
    return result;
}

Vector vDivide(Vector v1, Vector v2){
    Vector division = new_vector(v1.length);
    for (int i = 0; i<v1.length; i++){
        division.arr[i] = v1.arr[i] / v2.arr[i];
    }
    return division;
}

Vector vDivideF(Vector *v1, Vector *v2){
    Vector division = vDivide(*v1, *v2);
    free(v1->arr);
    free(v2->arr);
    return division;
}

Vector vDivideConst(Vector v, double n){
    Vector division = new_vector(v.length);
    for (int i = 0; i<v.length; i++){
        division.arr[i] = v.arr[i] / n;
    }
    return division;
}

Vector vDivideConstF(Vector *v, double n){
    Vector division = vDivideConst(*v, n);
    free(v->arr);
    return division;
}

void printVector(Vector v){
    for (int i = 0; i<v.length; i++){
        printf("%f ", v.arr[i]);
    }
    printf("\n");
}

double max(Vector v){
    double _max = -32768.0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]>_max){
            _max = v.arr[i];
        }
    }
    return _max;
}

double min(Vector v){
    double _min = 32768.0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]<_min){
            _min = v.arr[i];
        }
    }
    return _min;
}

double argMax(Vector v){
    double _max = -32768.0;
    int index = 0;
    for (int i = 0; i<v.length; i++){
        if (v.arr[i]>_max){
            _max = v.arr[i];
            index = i;
        }
    }
    return index;
}

double argMin(Vector v){
    double _min = 32768.0;
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

void vUpdateSumF(Vector *v, Vector *vals){
    vUpdateSum(v, *vals);
    free(vals->arr);
}