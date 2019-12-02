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
int movingAverageFilter(double* data, int data_size, int window_size, double* output_data)
{
    // Check to ensure window_size is smaller than the number of elements of the input data
    if (window_size > data_size)
    {
        printf("[Error] - Window Size: %i exceeds number of elements in data set: %i",window_size,data_size);
        return -1;  // Return negative number to imply error
    }
    else
        printf("Smoothing Window Size: %i\n", window_size);
    
    // Define output data size depending on input data size and smoothing window
    int output_data_size = data_size - (window_size - 1);

    // Loop through data and apply smoothing filter
    for (int i = 0; i < output_data_size; ++i)
    {
        double sum = 0;  // Clear sum value
        for (int j = 0; j < window_size; ++j)
        {
            sum += data[i+j];  // Sum data points within the active smoothing window
        }
        output_data[i]=sum/window_size;  // Averaged data accross window
    }
    return output_data_size;  // Return number of elements of output data
}