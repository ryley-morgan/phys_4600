#include <stdlib.h> /* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>  /* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>   /* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 
/*
File: task1.c
Author: Ryley Morgan <ryley.morgan@email.kpu.ca>
Modified from github.com/jhoyland/phys4600f19/task1/task1.c
*/


int main()
{
    float data [] ={0.068038, 0.173967, 0.439303, 0.615258, 0.789436, 0.770980, 0.890924, 1.034431, 0.955555, 0.991579, 0.919359, 0.857244, 0.680064, 0.558250, 0.473129, 0.278329, 0.027142, -0.151631, -0.454363, -0.534177, -0.803847, -0.882892, -0.996433, -0.919950, -1.068664, -1.000596, -0.997921, -0.909708, -0.607322, -0.611919, -0.380097, -0.127268};

    float mean;
    float std_dev;
    float sum = 0;
    float sum_variance = 0;
    int num_elements = 32;

    for (int i = 0; i < num_elements ; ++i)
    {
        /* Sum elements of array */ 
        sum = sum + data[i];
        printf("For array element %i \tElement = %f\t Sum = %f\n", i, data[i],sum);
    }

    mean = sum / num_elements; // Calculate Mean

    for (int i = 0; i < num_elements; ++i)
    {
        /* sum variances |X_i-X_avg|^2 */
        sum_variance = sum_variance + pow(abs(data[i]-mean),2);
        printf("For array element %i \tElement = %f\t sum_variance = %f\n", i, data[i],sum_variance);

    }

    std_dev = sqrt(sum_variance/num_elements); // Calculate the standard deviation

    printf("\nMean = %f", mean);
    printf("\nStandard deviation = %f", std_dev);

    
    return 0;  // Functions which return a value MUST contain at least one return statement
}




