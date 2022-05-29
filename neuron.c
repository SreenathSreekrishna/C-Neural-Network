#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Neuron {
    float value;
    float bias;
}

float getRand(){
    return (float)(rand() % 1000)/1000.0;
}

Neuron new_neuron(void) {
    Neuron neuron;
    neuron.value = getRand();
    neuron.bias = getRand();
    return neuron;
}