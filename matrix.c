#include <stdlib.h>
#include <stdio.h>
#include "vector_type.c"

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

int main(void){
    //empty
}