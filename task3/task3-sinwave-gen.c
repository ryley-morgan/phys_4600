#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    FILE * output_file;
    // Check for correct number of arguements
    if (argc != 3)
    {
        printf("Incorrect number of command line arguements.\n\tARGS: [number of divisions] [output-file-path]");
        return 1;
    }

    double start_value = 0;
    double end_value = M_PI;
    double num_divisions = atoi(argv[1]);
    printf("%f\n", num_divisions);
    double iteration = (end_value-start_value)/num_divisions;
    printf("%f\n", iteration );
    double current_value = start_value;
    output_file = fopen(argv[2],"w");

    while(current_value <= end_value){

        fprintf(output_file, "%f %f\n",current_value,sin(current_value));
        current_value = current_value+iteration;
    }
    fclose(output_file);
    return 0;
}