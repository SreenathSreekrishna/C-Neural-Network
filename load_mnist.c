#include <stdlib.h>
#include <stdio.h>
#ifndef __matrix__
#define __matrix__
#include "matrix.c"
#endif
#define COMPRESS_SIZE 7

typedef struct Data {
    Vector values;
    Vector label;
} Data;

void free_data(Data *data, int size){
    for (int i = 0; i<size; i++){
        free(data[i].values.arr);
    }
    free(data);
}

double processPixel(double pix){
    return (pix / 255.0) - 0.5;
}

Vector compressImg(Vector img, int n){
    int len = n*n;
    int end_length = img.length/len;
    Vector compressed = new_vector_null(end_length);
    for (int i = 0; i<end_length; i++){
        double _sum = 0.0;
        for (int j = 0; j<len; j++){
            _sum += img.arr[i*len+j];
        }
        compressed.arr[i] = _sum / len;
    }
    free(img.arr);
    return compressed;
}

Vector process(double label, Vector labels){
    Vector output = new_vector_zeroes(labels.length);
    for (int i = 0; i<labels.length; i++){
        if (labels.arr[i] == label){
            output.arr[i] = 1;
            return output;
        }
    }
    return output;
}

Data *load(Vector _labels){
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
        train_set[_].label = process(label[0], _labels);
        for (int i = 0; i<size; i++){
            vec.arr[i] = processPixel(buffer[i]);
        }
        train_set[_].values = compressImg(vec, COMPRESS_SIZE);
        cursor+=size;
    }
    fclose(file);
    fclose(labels);
    return train_set;
}

/*int main(void){
    Data *training = load();
    free_data(training, 60000);
}*/