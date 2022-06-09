#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float getRand(){
    return (((float)(rand() % 1000)/1000.0)*2)-1;
}

float ReLu(float n){
    if (n<0){
        return 0.0;
    }
    return n;
}

float ReLuDerivative(float n){
    if (n<0){
        return 0;
    }
    return 1;
}

float sig(float n) {
    return (n / (1 + fabsf(n)));
}

float sigDerivative(float n){
    return (n * (1 - n));
}