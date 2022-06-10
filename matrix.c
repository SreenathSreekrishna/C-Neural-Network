#include <stdlib.h>
#include <stdio.h>
#ifndef Vector
#define __matrix__
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

Matrix mFromVector(Vector v, int orientation){
    if (orientation==1){
        Matrix m = new_matrix(1,v.length);
        for (int i = 0; i<v.length; i++){
            m.arr[0].arr[i] = v.arr[i];
        }
        free(v.arr);
        return m;
    }
    Matrix m = new_matrix(v.length,1);
    for (int i = 0; i<v.length; i++){
        m.arr[i].arr[0] = v.arr[i];
    }
    free(v.arr);
    return m;
}

Matrix mMultiplyConst(Matrix m, float n){
    Matrix multiplication = new_matrix(m.dims[0],m.dims[1]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            multiplication.arr[i].arr[j] = m.arr[i].arr[j] * n;
        }
    }
    return multiplication;
}

Matrix transpose(Matrix m){
    Matrix transposed = new_matrix(m.dims[1], m.dims[0]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            transposed.arr[j].arr[i] = m.arr[i].arr[j];
        }
    }
    return transposed;
}

Vector mSum(Matrix m){
    Matrix flipped = transpose(m);
    Vector _sum = new_vector(m.dims[0]);
    for (int i = 0; i<flipped.dims[0]; i++){
        _sum.arr[i] = sum(flipped.arr[i]);
    }
    matrix_free(&flipped);
    return _sum;
}

Matrix mDot(Matrix m1, Matrix m2){
    Matrix second = transpose(m2);
    Matrix multiplication = new_matrix(m1.dims[0],m2.dims[1]);
    for (int i = 0; i<m1.dims[0]; i++){
        for (int j = 0; j<second.dims[0]; j++){
            Vector v = vMultiply(m1.arr[i], second.arr[j]);
            multiplication.arr[i].arr[j] = sum(v);
            free(v.arr);
        }
    }
    matrix_free(&second);
    return multiplication;
}

Matrix mApplyFunc(Matrix m, float (*f)(float)){
    Matrix end = new_matrix(m.dims[0], m.dims[1]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            end.arr[i].arr[j] = (*f)(m.arr[i].arr[j]);
        }
    }
    return end;
}