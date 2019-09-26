#ifndef __LOAD_DATA_H   //Include-guard for load-data.h
#define __LOAD_DATA_H   // Define load-data.h

#include <stdio.h>  // Input-output library necessary for interacting with system files

/*
    Load data x-y space separated data from input file.
    ARGS:
        double* x_data:                 pointer pointing to x-axis data from input_file
        double* y_data:                 pointer pointing to y-axis data from input_file
        const char* input_file_path:    system path to input_file containing sinusoidal wave data
    OUTPUT:
        int:                            number of data points loaded
*/
int loadData(double* x_data, double* y_data, const char* input_file_path);

#endif // End of include-guard