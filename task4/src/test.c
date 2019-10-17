#include <stdlib.h>
#include <stdio.h>
#include "add-noise.h"
#include "data-io.h"
#include "filters.h"
#include "sin-amplitude.h"

#define MAX_DATA_POINTS 255

int main(int argc, char const *argv[])
{
    // Allocate memory for storing up to 255 data points in arrays
    double noise_data[MAX_DATA_POINTS];
    double smooth_data[MAX_DATA_POINTS];
    double x_data[MAX_DATA_POINTS];
    double y_data[MAX_DATA_POINTS];

    int num_data_points;    // Calculated number of data points
    int save_result;        // Result of save command
    int smooth_data_size;   // Number of elements in smooth_data array based on filter window size
    double max_amplitude;   // Storing 


    // Check where data needs to be loaded from command line arguement
    if (argc >=2)
        num_data_points = loadData(x_data, y_data, argv[1]);
    else
        num_data_points = loadData(x_data, y_data, "data.dat");

    printf("Number of data points: %i\n", num_data_points);
    // Calculate the maximum amplitude of the original data sin wave
    max_amplitude=maxAmplitude(y_data, num_data_points);
    printf("Maximum Amplitude of original data: %lf\n",max_amplitude);

    // Apply noise to the curve by calling addNoise from "add-noise.h"
    addNoise(y_data, num_data_points, noise_data);
    // Calculate the maximum amplitude of the noise data sin wave
    max_amplitude=maxAmplitude(noise_data, num_data_points);
    printf("Maximum Amplitude of noisy data: %lf\n",max_amplitude);

    // Check where to store noisy data from command line arguement
    if (argc >=3)
        save_result = saveData(x_data, y_data, noise_data, num_data_points, argv[2]);
    else
        save_result = saveData(x_data, y_data, noise_data, num_data_points, "noisy-data.dat");

    // Check where to store smoothed data and the size of the smoothing filter
    if (argc == 5)
    {
        smooth_data_size = movingAverageFilter(y_data, num_data_points, atoi(argv[3]), smooth_data);
        save_result = saveData(x_data, noise_data, smooth_data, smooth_data_size, argv[4]);
    }
    else
    {
        smooth_data_size = movingAverageFilter(y_data, num_data_points, 5, smooth_data);
        save_result = saveData(x_data, noise_data, smooth_data, smooth_data_size, "smoothed-data.dat");
    }
    // Find the max amplitude fo the smoothed data
    max_amplitude=maxAmplitude(smooth_data, smooth_data_size);
    printf("Maximum Amplitude of smooth data: %lf\n",max_amplitude);
    return 0;
}