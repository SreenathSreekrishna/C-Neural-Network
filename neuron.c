#include <time.h>

float getRand(){
    return (float)(rand() % 1000)/1000.0;
}

float ReLu(float n){
    if (n<0){
        return 0.0;
    }
    return n;
}