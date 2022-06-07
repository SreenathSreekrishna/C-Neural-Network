#include <stdlib.h>
#include "network.c"
#include "load_mnist.c"
#include <time.h>

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

int convertLabel(int label, Vector labels){
    for (int i = 0; i<labels.length; i++){
        if (labels.arr[i] == label){
            return i;
        }
    }
    return -1;
}

float loss(Data data, Network *nn, Vector labels){
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
    float total = 0.0;
    printf("loss: %lf\n", loss(training[0],&nn,labels));
    printVector(nn.neuronLayers[3].neurons);
    free_data(training, 6000);
    free_network(&nn);
}