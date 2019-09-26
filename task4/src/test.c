#include <stdlib.h>
#include <stdio.h>
#include "sin-amplitude.h"
#include "load-data.h"

#define MAX_DATA_POINTS 255

int main(int argc, char const *argv[])
{
    double x_data [MAX_DATA_POINTS];
    double y_data [MAX_DATA_POINTS];

    int num_data_points = loadData(x_data, y_data, argv[1]);
    for (int i = 0; i < num_data_points; ++i)
    {
        printf("%f %f", x_data[i], y_data[i]);
    }

    double max_amplitude=maxAmplitude(y_data,num_data_points);
    
    return 0;
}