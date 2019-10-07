#include <stdio.h>

#define DATA_FORMAT "%lf %lf"

/*
    Load data x-y space separated data from input file.
    ARGS:
        double* x_data:                 pointer pointing to x-axis data from input_file
        double* y_data:                 pointer pointing to y-axis data from input_file
        const char* input_file_path:    system path to input_file containing sinusoidal wave data
    OUTPUT:
        int:                            number of data points loaded
*/
int loadData(double* x_data, double* y_data, const char* input_file_path){
    FILE * input_file;
    input_file = fopen(input_file_path,"r");
    int i = 0;
    printf("Input Data: \n x_data:\ty_data:\n");
    while(fscanf(input_file,DATA_FORMAT,&x_data[i],&y_data[i]) != EOF){
        printf(DATA_FORMAT"\n",x_data[i],y_data[i]);
        i++;
    }
    Printf("Number of values: %d", i);
    fclose(input_file);
    return i;
}