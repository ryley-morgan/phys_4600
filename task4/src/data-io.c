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
    printf("Number of values: %d\n", i);
    fclose(input_file);
    return i;
}

/*
    Save data x-y space separated data from input file.
    ARGS:
        double* x_data:                 pointer pointing to x-axis data to save to output_file
        double* y_data:                 pointer pointing to y-axis data to save to output_file
        const char* input_file_path:    system path to output_file to save sinusoidal data to
*/
int saveData(double* x_data, double* y_data, double* z_data, int num_of_values, const char* output_file_path){
    FILE * output_file;
    output_file = fopen(output_file_path,"w");
    printf("Opening file to write data to: %s\n", output_file_path);
    for (int i = 0; i < num_of_values; ++i)
    {
        int check = fprintf(output_file, DATA_FORMAT" %lf\n", x_data[i], y_data[i], z_data[i]);
        if (check <= 0)
        {
            printf("Error writting data to file: %s\n", output_file_path);
            return -1;
        }

    }
    printf("Saved data to file: %s\n", output_file_path);
    fclose(output_file);
    return 0;
}