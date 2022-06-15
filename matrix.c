#include <stdlib.h>
#include <stdio.h>
#ifndef Vector
#include "vector.c"
#endif

//NOTE: ALL FUNCTIONS ENDING WITH F WILL FREE ARGUMENT MATRICES AFTER OPERATION

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

void printDims(Matrix m){
    printf("%dx%d\n", m.dims[0], m.dims[1]);
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

Matrix new_matrix_zeros(int sizeX, int sizeY){
    Vector *mat = malloc((sizeX)*sizeof(Vector));
    for (int i = 0; i<sizeX; i++){
        Vector tmp = new_vector_zeroes(sizeY);
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
            double prod = matrixA.arr[i].arr[j] * matrixB.arr[i].arr[j];
            product.arr[i].arr[j] = prod;
        }
    }
    return product;
}

Matrix mMultiplyF(Matrix *matrixA, Matrix *matrixB) {
    Matrix product = mMultiply(*matrixA, *matrixB);
    matrix_free(matrixA);
    matrix_free(matrixB);
    return product;
}

Matrix mFromVector(Vector v, int orientation){
    if (orientation==1){
        Matrix m = new_matrix(1,v.length);
        for (int i = 0; i<v.length; i++){
            m.arr[0].arr[i] = v.arr[i];
        }
        return m;
    }
    Matrix m = new_matrix(v.length,1);
    for (int i = 0; i<v.length; i++){
        m.arr[i].arr[0] = v.arr[i];
    }
    return m;
}

Matrix mFromVectorF(Vector *v, int orientation){
    Matrix m = mFromVector(*v, orientation);
    free(v->arr);
    return m;
}

Vector vMultiplyO(Matrix v1, Matrix v2, int _i, int j){
    Vector prod = new_vector_zeroes(v1.dims[0]);
    for (int i = 0; i<v1.dims[0]; i++){
        prod.arr[i] = v1.arr[i].arr[_i] * v2.arr[j].arr[i];
    }
    return prod;
}

Matrix mMultiplyConst(Matrix m, double n){
    Matrix multiplication = new_matrix(m.dims[0],m.dims[1]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            multiplication.arr[i].arr[j] = m.arr[i].arr[j] * n;
        }
    }
    return multiplication;
}

Matrix mMultiplyConstF(Matrix *m, double n){
    Matrix multiplication = mMultiplyConst(*m, n);
    matrix_free(m);
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

Matrix transposeF(Matrix *m){
    Matrix transposed = transpose(*m);
    matrix_free(m);
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

Vector mSumF(Matrix *m){
    Vector _sum = mSum(*m);
    matrix_free(m);
    return _sum;
}

Matrix mDot(Matrix m1, Matrix m2){
    Matrix multiplication = new_matrix_zeros(m1.dims[0],m2.dims[1]);
    for (int i = 0; i<m1.dims[0]; i++){
        for (int j = 0; j<m2.dims[1]; j++){
            Vector v = vMultiplyO(m2, m1, j, i);
            multiplication.arr[i].arr[j] = sum(v);
            free(v.arr);
        }
    }
    return multiplication;
}

Matrix mDotF(Matrix *m1, Matrix *m2){
    Matrix multiplication = mDot(*m1, *m2);
    matrix_free(m1);
    matrix_free(m2);
    return multiplication;
}

Matrix mApplyFunc(Matrix m, double (*f)(double)){
    Matrix end = new_matrix(m.dims[0], m.dims[1]);
    for (int i = 0; i<m.dims[0]; i++){
        for (int j = 0; j<m.dims[1]; j++){
            end.arr[i].arr[j] = (*f)(m.arr[i].arr[j]);
        }
    }
    return end;
}

Matrix mApplyFuncF(Matrix *m, double (*f)(double)){
    Matrix end = mApplyFunc(*m, f);
    matrix_free(m);
    return end;
}

Matrix mAdd(Matrix m1, Matrix m2){
    Matrix _sum = new_matrix_zeros(m1.dims[0], m2.dims[1]);
    for (int i = 0; i<m1.dims[0]; i++){
        for (int j = 0; j<m2.dims[1]; j++){
            _sum.arr[i].arr[j] = m1.arr[i].arr[j] + m2.arr[i].arr[j];
        }
    }
    return _sum;
}

Matrix mAddF(Matrix *m1, Matrix *m2){
    Matrix _sum = mAdd(*m1, *m2);
    matrix_free(m1);
    matrix_free(m2);
    return _sum;
}

Vector vFromMatrix(Matrix m){
    int len = m.dims[0]==1 ? m.dims[1] : m.dims[0];
    Vector v = new_vector_zeroes(len);
    for (int i = 0; i<len; i++){
        if (m.dims[0]==1){
            v.arr[i] = m.arr[0].arr[i];
        }
        else {
            v.arr[i] = m.arr[i].arr[0];
        }
    }
    return v;
}

Vector vFromMatrixF(Matrix *m){
    Vector v = vFromMatrix(*m);
    matrix_free(m);
    return v;
}

void updateSum(Matrix *m, Matrix v){
    for (int i = 0; i<v.dims[0]; i++){
        for (int j = 0; j<v.dims[1]; j++){
            m->arr[i].arr[j] = m->arr[i].arr[j] + v.arr[i].arr[j];
        }
    }
}

void updateSumF(Matrix *m, Matrix *v){
    updateSum(m, *v);
    matrix_free(v);
}