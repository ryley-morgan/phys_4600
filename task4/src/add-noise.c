#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void addNoise(double* data, int n, double* noisy_data){
    srand(time(NULL));  // max rand based on current system time
    for (int i = 0; i < n; ++i)
    {
        float r1 = (float) rand()/(float) RAND_MAX;
        float r2 = (float) rand()/(float) RAND_MAX;

        float perturbation = r1-r2/1000;
        noisy_data[i]=data[i]+perturbation;

        printf("Data: %lf\t Noisy_data: %lf\n",data[i], noisy_data[i]);
    }

}
