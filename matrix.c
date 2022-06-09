#include <stdlib.h>
#include <stdio.h>
#ifndef Vector
#include "vector.c"
#endif
#include <stdlib.h>
#include <stdio.h>

typedef struct Matrix {
    Vector *arr;
    int dims[2];
} Matrix;

void printMatrix(Matrix mat){
    for (int i = 0; i<mat.dims[0] ; i++){
        for (int j = 0; j<mat.dims[1]; j++){
            printf("%lf ", mat.arr[i].arr[j]);
        }
        printf("\n");
    }
}


void matrix_free(Matrix *matrix){
    for (int i = 0; i<matrix->dims[0] ; i++){
        free(matrix->arr[i].arr);
    }
    free(matrix->arr);
}

Matrix new_matrix(int sizeX, int sizeY){
    /*
    size 3,2 would give - 
    [
        [a,b],
        [c,d],
        [e,f]
    ]
    */
    Vector *mat = malloc((sizeX)*sizeof(Vector));
    for (int i = 0; i<sizeX; i++){
        Vector tmp = new_vector(sizeY);
        mat[i] = tmp;
    }
    Matrix matrix;
    matrix.arr = mat;
    matrix.dims[0] = sizeX;
    matrix.dims[1] = sizeY;
    return matrix;
}

Matrix mMultiply(Matrix matrixA, Matrix matrixB) {
    Matrix product = new_matrix(matrixA.dims[0], matrixA.dims[1]);
    for (int i = 0; i<matrixA.dims[0]; i++){
        for (int j = 0; j<matrixA.dims[1]; j++){
            float prod = matrixA.arr[i].arr[j] * matrixB.arr[i].arr[j];
            product.arr[i].arr[j] = prod;
        }
    }
    return product;
}

Matrix mFlip(Matrix m){
    Matrix flipped = new_matrix(m.dims[1], m.dims[0]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            flipped.arr[j].arr[i] = m.arr[i].arr[j];
        }
    }
    return flipped;
}

Vector mSum(Matrix m){
    Matrix flipped = mFlip(m);
    Vector _sum = new_vector(m.dims[0]);
    for (int i = 0; i<flipped.dims[0]; i++){
        _sum.arr[i] = sum(flipped.arr[i]);
    }
    matrix_free(&flipped);
    return _sum;
}