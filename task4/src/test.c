#include <stdlib.h>
#include <stdio.h>
#include "sin-amplitude.h"
#include "data-io.h"
#include "add-noise.h"

#define MAX_DATA_POINTS 255

int main(int argc, char const *argv[])
{

    double x_data[MAX_DATA_POINTS];
    double y_data[MAX_DATA_POINTS];
    double noise_data[MAX_DATA_POINTS];
    int num_data_points;
    int save_result;

    if (argc >=1)
    {
        num_data_points = loadData(x_data, y_data, argv[1]);
        printf("Number of data points: %i\n", num_data_points);
    }

    addNoise(y_data,num_data_points,noise_data);

    if (argc =2)
    {
        save_result = saveData(x_data, y_data, noise_data, num_data_points, argv[2]);
    }

    
    double max_amplitude=maxAmplitude(y_data,num_data_points);
    printf("Maximum Amplitude of Clean data: %lf\n",max_amplitude);
    max_amplitude=maxAmplitude(noise_data,num_data_points);
    printf("Maximum Amplitude of noisy data: %lf\n",max_amplitude);
    return 0;
}