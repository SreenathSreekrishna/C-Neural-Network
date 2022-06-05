#include <stdlib.h>
#include "network.c"
#include "load_mnist.c"

Vector compute(Vector input, Network nn){
    //Computes output neuron activations given the input neuron activations
    nn.neuronLayers[0].neurons = input;
    for (int i = 0; i<nn.size-1; i++){
        for (int j = 0; j<nn.neuronLayers[i+1].neurons.length; j++){
            float result = nn.neuronLayers[i+1].biases.arr[j] + vDot(nn.neuronLayers[i].neurons, nn.weightLayers[i].weights.arr[j]);
            nn.neuronLayers[i+1].neurons.arr[j] = ReLu(result);
        }
    }
    return nn.neuronLayers[nn.size-1].neurons;
}

int convertLabel(int label, Vector labels){
    for (int i = 0; i<labels.length; i++){
        if (labels.arr[i] == label){
            return i;
        }
    }
}

float loss(Data data, Network nn, Vector labels){
    Vector output = compute(data.values, nn);
    Vector expected = new_vector(output.length);
    for (int i = 0; i<expected.length; i++){
        expected.arr[i] = 0.0;
    }
    expected.arr[convertLabel(data.label, labels)] = 1.0;
    Vector diff = vSub(output, expected);
    Vector __loss = vSquare(diff);
    float _loss = sum(__loss);
    free(__loss.arr);
    free(diff.arr);
    free(expected.arr);
    return _loss;
}