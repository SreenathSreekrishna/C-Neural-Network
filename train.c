#include "network.c"

Vector compute(Vector input, Network nn){
    //Computes output neuron activations given the input neuron activations
    nn.neuronLayers[0].neurons = input;
    for (int i = 0; i<nn.size-1; i++){
        for (int j = 0; j<nn.neuronLayers[i+1].neurons.length; j++){
            float result = nn.neuronLayers[i+1].biases.arr[j] + vDot(nn.neuronLayers[i].neurons, nn.weightLayers[i].weights.arr[j]);
            nn.neuronLayers[i+1].neurons.arr[j] = result;
        }
    }
    return nn.neuronLayers[nn.size-1].neurons;
}