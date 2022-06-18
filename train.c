#include <stdlib.h>
#include "network.c"
#include "load_mnist.c"
#include <time.h>
#define LEARNING_RATE 0.1
#define INPUT 16
#define HIDDEN 20
#define OUTPUT 10
#define EPOCHS 10000
#define NUM_IMGS 1000
#define BATCH_SIZE 100
#define _time 0

int main(void){
    double total_prop = 0.0;
    srand(time(NULL));
    double arr[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Vector labels;
    labels.length = 10;
    labels.arr = arr;
    Data *training = load(labels);
    Matrix w_i_h = new_matrix(HIDDEN,INPUT);
    Matrix w_h_o = new_matrix(OUTPUT, HIDDEN);
    Vector b_i_h = new_vector_zeroes(20);
    Vector b_h_o = new_vector_zeroes(10);
    int correct = 0;
    for (int epoch = 0; epoch<EPOCHS; epoch++){
        double cost = 0.0;
        int num_batches = NUM_IMGS / BATCH_SIZE;
        for (int batch = 0; batch<num_batches; batch++){
            Matrix gradient_w_i_h = new_matrix_zeros(w_i_h.dims[0], w_i_h.dims[1]);
            Matrix gradient_w_h_o = new_matrix_zeros(w_h_o.dims[0], w_h_o.dims[1]);
            Vector gradient_b_i_h = new_vector_zeroes(b_i_h.length);
            Vector gradient_b_h_o = new_vector_zeroes(b_h_o.length);
            for (int img = 0; img<BATCH_SIZE; img++){
                int trainExample = batch*BATCH_SIZE+img;
                struct timespec start, end;
                if (_time){
                    clock_gettime(CLOCK_REALTIME, &start);
                }

                Vector img = training[trainExample].values;
                Vector label = training[trainExample].label;

                //input ->  hidden
                Matrix imgM = mFromVector(img, 0);
                Matrix mbih = mFromVector(b_i_h, 0);
                Matrix weightedVals = mDot(w_i_h, imgM);
                Matrix weightedSum  = mAddF(&mbih, &weightedVals);
                Matrix h = mApplyFuncF(&weightedSum, sig);
                matrix_free(&imgM);

                //hidden ->  output
                Matrix mbho = mFromVector(b_h_o, 0);
                Matrix weightedSumO = mDot(w_h_o, h);
                Matrix o_pre = mAddF(&mbho, &weightedSumO);
                Matrix oM = mApplyFuncF(&o_pre, sig);
                Vector o = vFromMatrixF(&oM);

                //cost
                Vector diff = vSub(label, o);
                Vector _cost = vSquareF(&diff);
                cost += sumF(&_cost);
                if (argMax(o) == argMax(label)){
                    correct += 1;
                }

                //backprop output -> hidden
                Vector delta_oV = vSub(o,label);
                free(o.arr);
                Matrix delta_o = mFromVectorF(&delta_oV, 0);
                Matrix ht = transpose(h);
                Matrix nudgesBig = mDot(delta_o, ht);
                matrix_free(&ht);
                Matrix nudges = mMultiplyConstF(&nudgesBig, -LEARNING_RATE);
                updateSumF(&gradient_w_h_o, &nudges);
                Matrix bNudgesM = mMultiplyConst(delta_o, -LEARNING_RATE);
                Vector bNudges = vFromMatrixF(&bNudgesM);
                vUpdateSumF(&gradient_b_i_h, &bNudges);

                //backprop hidden -> input
                Matrix vht = transpose(w_h_o);
                Matrix hd = mApplyFuncF(&h, sigDerivative);
                Matrix prod = mDotF(&vht, &delta_o);
                Matrix delta_h = mMultiplyF(&prod, &hd);
                Matrix imgT = mFromVector(img, 1);
                Matrix nudgesBigh = mDot(delta_h, imgT);
                matrix_free(&imgT);
                Matrix nudgesh = mMultiplyConstF(&nudgesBigh, -LEARNING_RATE);
                updateSumF(&gradient_w_i_h, &nudgesh);
                Matrix bNudgesMh = mMultiplyConstF(&delta_h, -LEARNING_RATE);
                Vector bNudgesh = vFromMatrixF(&bNudgesMh);
                vUpdateSumF(&gradient_b_i_h, &bNudgesh);

                if(_time){
                    clock_gettime(CLOCK_REALTIME, &end);
                    double time_spent = (end.tv_sec - start.tv_sec) +
                                        (end.tv_nsec - start.tv_nsec) / 1000000000.0;
                    total_prop+=time_spent;
                }
            }
            Matrix wihavg = mDivideConstF(&gradient_w_i_h, num_batches);
            Matrix whoavg = mDivideConstF(&gradient_w_h_o, num_batches);
            Vector bihavg = vDivideConstF(&gradient_b_i_h, num_batches);
            Vector bhoavg = vDivideConstF(&gradient_b_h_o, num_batches);
            updateSumF(&w_i_h, &wihavg);
            updateSumF(&w_h_o, &whoavg);
            vUpdateSumF(&b_i_h, &bihavg);
            vUpdateSumF(&b_h_o, &bhoavg);
        }
        printf("Accuracy on epoch %d: %f\n", epoch, (double) correct / (double) NUM_IMGS);
        printf("Cost on epoch %d: %f\n", epoch, cost/NUM_IMGS);
        if (_time){
            printf("Time taken on epoch %d: %f\n", epoch, total_prop);
            total_prop = 0;
        }
        printf("\n");
        correct = 0;
    }
    matrix_free(&w_i_h);
    matrix_free(&w_h_o);
    free(b_i_h.arr);
    free(b_h_o.arr);
    free_data(training, 60000);
}