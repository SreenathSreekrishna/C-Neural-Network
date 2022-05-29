#include <stdlib.h>
#include <stdio.h>
#include "vector_type.c"

typedef struct Data {
    Vector values;
    int label;
} Data;

void free_data(Data *data, int size){
    for (int i = 0; i<size; i++){
        free(data[i].values.arr);
    }
    free(data);
}

Data *load(void){
    FILE *file,*labels;
    file = fopen("mnist/trainimgs", "rb");
    labels = fopen("mnist/trainlabels","rb");
    int num_imgs = 60000;
    int cursor = 16;
    int size = 784;
    Data *train_set = malloc(sizeof(Data)*num_imgs);
    for (int _ = 0; _<num_imgs; _++){
        fseek(labels,_,0);
        fseek(file,cursor,0);
        unsigned char buffer[size];
        unsigned char label[1];
        fread(buffer,size,1,file);
        fread(label,1,1,labels);
        Vector vec = new_vector(size);
        train_set[_].label = label[0];
        for (int i = 0; i<size; i++){
            vec.arr[i] = (float) buffer[i] / 255.0;
        }
        train_set[_].values = vec;
        cursor+=size;
    }
    fclose(file);
    fclose(labels);
    return train_set;
}

int main(void){
    Data *training = load();
    free_data(training, 60000);
}