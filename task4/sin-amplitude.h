#ifndef __SIN_AMPLITUDE_H   //Include-Guard
#define __SIN_AMPLITUDE_H   

/*
    Find the maximum absolute amplitude of a sin wave.
    INPUT ARGS:
        double* data:   array of sinusoidal wave amplitudes
        int n:          number of data points
    OUTPUT:
        double:         value of maximum absolute amplitude
*/
double maxAmplitude(double* data, int n);

#endif