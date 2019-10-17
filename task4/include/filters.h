#ifndef __FILTERS_H  // Include guard!
#define __FILTERS_H  // Define filters.h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Apply moving average Filter to data and store in output_data
    ARGS:
        double* data:                   pointer pointing to input data
        int data_size:                  number of elements of input data
        int window_size:                size of smoothing window
        double* output_data:            pointer pointing to output data
    OUTPUT:
        int:                            number of elements of output data (error code: -1)
*/
int movingAverageFilter(double* data, int data_size, int window_size, double* output_data);

#endif  // End of Include Guard