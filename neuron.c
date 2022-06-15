#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double getRand(){
    return ((double)(rand() % 1000)/1000.0)-0.5;
}

double ReLu(double n){
    if (n<0){
        return 0.0;
    }
    return n;
}

double ReLuDerivative(double n){
    if (n<0){
        return 0;
    }
    return 1;
}

double sig(double n) {
    return (1 / (1 + exp(-n)));
}

double sigDerivative(double n){
    return (n * (1 - n));
}