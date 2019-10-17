#ifndef __ADD_NOISE_H  // Include Guard!
#define __ADD_NOISE_H  // Define add-noise.h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
    Add random noise to input data and save in pointer to output data
    ARGS:
        double* data:                   pointer pointing to input data
        int n:                          number of input data points
        double* noisy_data:             pointer pointing to output data
*/
void addNoise(double* data, int n, double* noisy_data);

#endif // End of Include Guard!