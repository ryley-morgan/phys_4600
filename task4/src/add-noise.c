#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
    Add random noise to input data and save in pointer to output data
    ARGS:
        double* data:                   pointer pointing to input data
        int n:                          number of input data points
        double* noisy_data:             pointer pointing to output data
*/
void addNoise(double* data, int n, double* noisy_data){
    srand(time(NULL));  // max rand based on current system time
    // loop through data points and apply perturbation
    for (int i = 0; i < n; ++i)
    {
        // Calculate perturbation based on two random numbers and apply to data
        float r1 = (float) rand()/(float) RAND_MAX;
        float r2 = (float) rand()/(float) RAND_MAX;
        float perturbation = r1-r2/1000;
        noisy_data[i]=data[i]+perturbation;
        // Print debugging statements
        printf("Data: %lf\t Noisy_data: %lf\n",data[i], noisy_data[i]);
    }
}