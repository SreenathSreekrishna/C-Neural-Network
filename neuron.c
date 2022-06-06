#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float getRand(){
    return (((float)(rand() % 1000)/1000.0)*2)-1;
}

float ReLu(float n){
    if (n<0){
        return 0.0;
    }
    return n;
}