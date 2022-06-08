#include <stdlib.h>
#define __matrix__
#include "matrix.c"

typedef struct WeightLayer {
    Matrix weights;
} WeightLayer;

typedef struct NeuronLayer {
    Vector neurons;
    Vector biases;
} NeuronLayer;

typedef struct Network {
    WeightLayer *weightLayers;
    NeuronLayer *neuronLayers;
    int size;
} Network;

Network create_network(Vector size){
    //size vector will have size of network in format [l1Size, l2Size, l3Size ...]
    Network nn;
    nn.weightLayers = malloc(sizeof(WeightLayer)*(size.length-1));
    nn.neuronLayers = malloc(sizeof(NeuronLayer)*size.length);
    for (int i = 0; i<size.length; i++){
        nn.neuronLayers[i].neurons = new_vector(size.arr[i]);
        nn.neuronLayers[i].biases =  new_vector(size.arr[i]);
    }
    int len = size.length-1;
    for (int i = 0; i<len; i++){
        //weightlayerMatrix[a][b] will return connection between ath neuron in curr layer and bth neuron in next layer
        nn.weightLayers[i].weights = new_matrix(nn.neuronLayers[i].neurons.length, nn.neuronLayers[i+1].neurons.length);
    }
    nn.size = size.length;
    return nn;
}

void free_network(Network *nn){
    for (int i = 0; i<nn->size; i++){
        free(nn->neuronLayers[i].neurons.arr);
        free(nn->neuronLayers[i].biases.arr);
    }
    int len = nn->size-1;
    for (int i = 0; i<len; i++){
        matrix_free(&(nn->weightLayers[i].weights));
    }
    free(nn->weightLayers);
    free(nn->neuronLayers);
}