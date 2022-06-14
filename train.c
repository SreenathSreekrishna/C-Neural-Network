#include <stdlib.h>
#include "network.c"
#include "load_mnist.c"
#include <time.h>
#define LEARNING_RATE 0.01
#define EPOCHS 50
#define NUM_IMGS 10000

int main(void){
    srand(time(NULL));
    float arr[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Vector labels;
    labels.length = 10;
    labels.arr = arr;
    Data *training = load(labels);
    Matrix w_i_h = new_matrix(20,784);
    Matrix w_h_o = new_matrix(10, 20);
    Vector b_i_h = new_vector_zeroes(20);
    Vector b_h_o = new_vector_zeroes(10);
    int correct = 0;
    for (int epoch = 0; epoch<EPOCHS; epoch++){
        float cost = 0.0;
        for (int trainExample = 0; trainExample<NUM_IMGS; trainExample++){
            Vector img = training[trainExample].values;
            Vector label = training[trainExample].label;

            //input ->  hidden
            Matrix imgM = mFromVector(img, 0);
            Matrix weightedSum = mDot(w_i_h, imgM);
            matrix_free(&imgM);
            Matrix mbih = mFromVector(b_i_h, 0);
            Matrix h_pre = mAdd(mbih, weightedSum);
            matrix_free(&mbih);
            matrix_free(&weightedSum);
            Matrix h = mApplyFunc(h_pre, sig);
            matrix_free(&h_pre);

            //hidden ->  output
            Matrix weightedSumo = mDot(w_h_o, h);
            Matrix mbho = mFromVector(b_h_o, 0);
            Matrix o_pre = mAdd(mbho, weightedSumo);
            matrix_free(&mbho);
            matrix_free(&weightedSumo);
            Matrix oM = mApplyFunc(o_pre, sig);
            matrix_free(&o_pre);
            Vector o = vFromMatrix(oM);
            //printVector(o);
            //printVector(label);
            //printf("\n");
            matrix_free(&oM);

            //cost
            Vector diff = vSub(label, o);
            Vector _cost = vSquare(diff);
            free(diff.arr);
            cost += sum(_cost);
            free(_cost.arr);
            if (argMax(o) == argMax(label)){
                correct += 1;
            }

            //backprop output -> hidden
            Vector delta_oV = vSub(o,label);
            free(o.arr);
            Matrix delta_o = mFromVector(delta_oV, 0);
            free(delta_oV.arr);
            Matrix ht = transpose(h);
            Matrix nudgesBig = mDot(delta_o, ht);
            matrix_free(&ht);
            Matrix nudges = mMultiplyConst(nudgesBig, -LEARNING_RATE);
            matrix_free(&nudgesBig);
            updateSum(&w_h_o, nudges);
            matrix_free(&nudges);
            Matrix bNudgesM = mMultiplyConst(delta_o, -LEARNING_RATE);
            Vector bNudges = vFromMatrix(bNudgesM);
            matrix_free(&bNudgesM);
            vUpdateSum(&b_i_h, bNudges);
            free(bNudges.arr);

            //backprop hidden -> input
            Matrix vht = transpose(w_h_o);
            Matrix hd = mApplyFunc(h, sigDerivative);
            matrix_free(&h);
            Matrix prod = mMultiply(delta_o, hd);
            matrix_free(&delta_o);
            matrix_free(&hd);
            Matrix delta_h = mDot(vht, prod);
            matrix_free(&vht);
            matrix_free(&prod);
            Matrix imgT = mFromVector(img, 1);
            Matrix nudgesBigh = mDot(delta_h, imgT);
            matrix_free(&imgT);
            Matrix nudgesh = mMultiplyConst(nudgesBigh, -LEARNING_RATE);
            matrix_free(&nudgesBigh);
            updateSum(&w_i_h, nudgesh);
            matrix_free(&nudgesh);
            Matrix bNudgesMh = mMultiplyConst(delta_h, -LEARNING_RATE);
            Vector bNudgesh = vFromMatrix(bNudgesMh);
            matrix_free(&bNudgesMh);
            matrix_free(&delta_h);
            vUpdateSum(&b_i_h, bNudgesh);
            free(bNudgesh.arr);
        }
        printf("Accuracy on epoch %d: %lf\n", epoch, (float) correct / (float) NUM_IMGS);
        printf("Cost on epoch %d: %lf\n\n", epoch, cost/NUM_IMGS);
        correct = 0;
    }
    matrix_free(&w_i_h);
    matrix_free(&w_h_o);
    free(b_i_h.arr);
    free(b_h_o.arr);
    free_data(training, 60000);
}