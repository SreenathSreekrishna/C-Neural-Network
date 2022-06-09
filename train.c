#include <stdlib.h>
#include "network.c"
#include "load_mnist.c"
#include <time.h>
#define TRAINING_SPEED 0.01

Vector compute(Vector input, Network *nn){
    //Computes output neuron activations given the input neuron activations
    for (int i = 0; i<input.length; i++){
        nn->neuronLayers[0].neurons.arr[i] = input.arr[i];
    }
    for (int i = 0; i<nn->size-1; i++){
        for (int j = 0; j<nn->neuronLayers[i+1].neurons.length; j++){
            float result = nn->neuronLayers[i+1].biases.arr[j] + vDot(nn->neuronLayers[i].neurons, nn->weightLayers[i].weights.arr[j]);
            float finalVal;
            if (i>=nn->size-2){
                finalVal = sig(result);
            }
            else {
                finalVal = ReLu(result);
            }
            nn->neuronLayers[i+1].neurons.arr[j] = finalVal;
        }
    }
    return nn->neuronLayers[nn->size-1].neurons;
}

Vector convertLabel(int label, Vector labels){
    Vector expected = new_vector(labels.length);
    for (int i = 0; i<expected.length; i++){
        expected.arr[i] = 0.0;
    }
    for (int i = 0; i<labels.length; i++){
        if (labels.arr[i] == label){
            expected.arr[i] = 1.0;
        }
    }
    return expected;
}

Vector getDiff(Data data, Network *nn, Vector labels){
    Vector output = compute(data.values, nn);
    Vector expected = convertLabel(data.label, labels);
    Vector diff = vSub(expected, output);
    free(expected.arr);
    return diff;
}

Vector backProp(Vector nudges, Matrix *wLayer){
    //returns nudges to weights in proportion to prev layer
    //todo
}

float loss(Data data, Network *nn, Vector labels){
    Vector diff = getDiff(data, nn, labels);
    Vector __loss = vSquare(diff);
    float _loss = sum(__loss);
    free(__loss.arr);
    free(diff.arr);
    return _loss;
}

int main(void){
    srand(time(NULL));
    Data *training = load();
    Vector size;
    float arr[] = {784.0, 16.0, 16.0, 10.0};
    float _labels[] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    Vector labels;
    labels.length = 10;
    labels.arr = _labels;
    size.arr = arr;
    size.length = 4;
    Network nn = create_network(size);
    free_data(training, 6000);
    free_network(&nn);
}