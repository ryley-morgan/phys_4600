#include <stdlib.h>
#include <stdio.h>
#include "sin-amplitude.h"
#include "load-data.h"
#include "add-noise.h"

#define MAX_DATA_POINTS 255

int main(int argc, char const *argv[])
{

    double x_data [MAX_DATA_POINTS];
    double y_data [MAX_DATA_POINTS];
    double noise_data [MAX_DATA_POINTS];

    int num_data_points = loadData(x_data, y_data, argv[1]);


    double max_amplitude=maxAmplitude(y_data,num_data_points);

    printf("Maximum Amplitude: %lf",max_amplitude)
    
    return 0;
}