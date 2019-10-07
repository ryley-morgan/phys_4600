#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int movingAverageFilter(double* data, int data_size, const char* window_size_char, double* output_data)
{
    int window_size = (int) *window_size_char;
    if (window_size > data_size)
    {
        printf("[Error] - Window Size: %i exceeds number of elements in data set: %i",window_size,data_size);
    }

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