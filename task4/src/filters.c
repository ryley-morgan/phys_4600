#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Apply moving average Filter to data and store in output_data
    ARGS:
        double* data:                   pointer pointing to x-axis data from input_file
        double* y_data:                 pointer pointing to y-axis data from input_file
        const char* input_file_path:    system path to input_file containing sinusoidal wave data
    OUTPUT:
        int:                            number of data points loaded
*/
int movingAverageFilter(double* data, int data_size, int window_size, double* output_data)
{
    if (window_size > data_size)
    {
        printf("[Error] - Window Size: %i exceeds number of elements in data set: %i",window_size,data_size);
    }
    else
        printf("Smoothing Window Size: %i\n", window_size);
    
    int output_data_size = data_size - (window_size - 1);

    for (int i = 0; i < output_data_size; ++i)
    {
        double sum = 0;
        for (int j = 0; j < window_size; ++j)
        {
            sum += data[i+j];
        }
        output_data[i]=sum/window_size;
    }
    return output_data_size;
}