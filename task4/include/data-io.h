#ifndef __DATA_IO_H  // Include guard!
#define __DATA_IO_H  // Define data-io.h

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

/*
    Save data x-y space separated data from input file.
    ARGS:
        double* x_data:                 pointer pointing to x-axis data to save to output_file
        double* y_data:                 pointer pointing to y-axis data to save to output_file
        double* z_data:                 pointer pointing to z-axis data to save to output_file
        const char* input_file_path:    system path to output_file to save sinusoidal data to
        int num_of_values               size of z-axis data array
*/
int saveData(double* x_data, double* y_data, double* z_data, int num_of_values, const char* output_file_path);

#endif // End of Include-guard