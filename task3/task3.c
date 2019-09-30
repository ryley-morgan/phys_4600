#include <stdlib.h> /* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>  /* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>   /* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 
/*
File: task3.c
Author: Ryley Morgan <ryley.morgan@email.kpu.ca>
Modified from github.com/jhoyland/phys4600f19/task1/task1.c
*/

/*
    Calculates the average and standard deviation of the population of.
    ARGS:
        float* array:           array of sample data
        int len:                length of array
        float* avg_cursor:      pointer pointing to average of sample data
        float* std_dev_cursor:  pointer pointing to standard deviation of sample data
*/

/*JAMES: Nice,and good commenting. Could do with a catch for if len==0 or 1 or if any of the pointers are NULL*/

void averageWithStandardDeviation(float* array, int len, float* avg_cursor, float* std_dev_cursor){
    float total = 0;
    float total_2 = 0;
    float avg = 0;
    float std_dev = 0;

    for (int i = 0; i < len ; ++i)
    {
        /* Sum elements of array */ 
        total = total + *array;
        total_2 = total_2 + pow(*array,2);
        array++;
    }
    //printf("\nTotal x_i \t%f",total); //Debug Statement
    //printf("\nTotal x_i^2\t%f",total_2);    //Debug Statement
    avg = total / len;
    *avg_cursor = avg;
    std_dev = sqrt((total_2 - (total*total/len))/(len-1));
    *std_dev_cursor = std_dev;
}

int main(int argc, char const *argv[])
{

    FILE * input_file;  // Define input file pointer

    int check_flag=0;   // Check for correct number of arguements
    int i = 0;  // Iterator for number of elements read in from the input file
    int max_data_size=1000; //Preallocate array sizes to prevent stack-smash and memory overflow
    int num_elements;   // Number of elements read in from the input file

    // Check for the correct number of elements and exit if not the correct amount
    if (argc != 2)
    {
        printf("Incorrect number of command line arguements.\n\tARGS: [input_file]");
        return 1;
    }

    input_file = fopen(argv[1],"r");    //Open input file to read

    /*JAMES: Check if fopen was successful */

    // Define the data array for reading the input file with size = max_data_size to prevent stach smash
    float x [max_data_size];
    float y [max_data_size];

    
    while(1==1)  /*JAMES: can just say while(1) */
    {
        check_flag = fscanf(input_file, "%f %f",&x[j],&y[j]);
        if (check_flag < 2)
        {
            break;
        }
        i++;

        if ( i >= max_data_size )
        {
            printf("Maximum number of samples (%i) reached.\n", max_data_size);
            break;
                    }
    }
    num_elements = i;
    fclose(input_file); 
    float mean;
    float standard_deviation;
    averageWithStandardDeviation(y, num_elements, &mean, &standard_deviation);
    printf("\nMean =\t%f", mean); // Return main
    printf("\nStandard deviation = %f", standard_deviation);
    return 0;  // Functions which return a value MUST contain at least one return statement
}

/*JAMES: Good user messages and source commenting */