typedef struct Vector {
    float *arr;
    int length;
} Vector;

Vector new_vector(int length){
    Vector vector;
    float *vecarr = malloc((length+1)*sizeof(float));
    for (int i = 0; i<length; i++){
        vecarr[i] = 1.0;
    }
    vecarr[length] = 0;
    vector.arr = vecarr;
    vector.length = length;
    return vector;
}