#include <math.h>
/*
File: sin-amplitude.c
Author: Ryley Morgan <ryley-morgan@github.com>

Determines the absolute amplitude of a sinusoidal wave
*/

/*
    Find the maximum absolute amplitude of a sin wave.
    INPUT ARGS:
        double* data:   array of sinusoidal wave amplitudes
        int n:          number of data points
    OUTPUT:
        double:         value of maximum absolute amplitude
*/
double maxAmplitude(double* data, int n)
{
    double max_value=0;     //Initialize max_value
    double min_value=0;     //Initialize min_value

    // Loop through all data points in array
    for (int i = 0; i < n; ++i)
    {
        // Replace max value if new value is greater than current max
        if (data[i] > max_value)
        {
            max_value = data[i];    
        }
        // Replace min value if new value is less than current min
        if (data[i] < min_value)
        {
            min_value = data[i];    
        }
    }
    
    double max_amplitude = fabs(max_value-min_value)/2;  // Calculate absolute max amplitude from max/min values
    return max_amplitude;   // Return max amplitude
}