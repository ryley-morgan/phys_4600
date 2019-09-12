#include <stdlib.h> /* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>  /* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>   /* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 
/*
File: task2.c
Author: Ryley Morgan <ryley.morgan@email.kpu.ca>
Modified from github.com/jhoyland/phys4600f19/task1/task1.c
*/

float average(float* array, int len){
    float total = 0;
    float avg = 0;
    for (int i = 0; i < len ; ++i)
    {
        /* Sum elements of array */ 
        total = total + array[i];
    }
    avg = total / len; // Calculate Mean
    return avg;
}

float standardDeviation(float* array, int len, float average){
    float sum_var = 0;
    float std_dev = 0;
    for (int i = 0; i < len ; ++i)
    {
        /* sum variances |X_i-X_avg|^2 */
        sum_var = sum_var + pow(abs(array[i]-average),2);
    }
    std_dev = sqrt(sum_var/len); // Calculate the standard deviation
    return std_dev;
}

int averageWithStandardDeviation(float* array, int len){
    float total = 0;
    for (int i = 0; i < len ; ++i)
    {
        /* Sum elements of array */ 
        total = total + array[i];
    }
    avg = total / len; // Calculate Mean
    printf("\nMean = %f", avg);

}

int main()
{
    float data [] ={0.068038, 0.173967, 0.439303, 0.615258, 0.789436, 0.770980, 0.890924, 1.034431, 0.955555, 0.991579, 0.919359, 0.857244, 0.680064, 0.558250, 0.473129, 0.278329, 0.027142, -0.151631, -0.454363, -0.534177, -0.803847, -0.882892, -0.996433, -0.919950, -1.068664, -1.000596, -0.997921, -0.909708, -0.607322, -0.611919, -0.380097, -0.127268};

    float mean;
    float standard_deviation;
    int num_elements = 32;

    mean = average(data,num_elements);
    standard_deviation = standardDeviation(data,num_elements,mean);

    printf("<-Part 1->")
    printf("\nMean = %f", mean);
    printf("\nStandard deviation = %f", standard_deviation);


    printf("<-Part 2->")
    printf("\nMean = %f", mean);
    printf("\nStandard deviation = %f", standard_deviation);
    
    return 0;  // Functions which return a value MUST contain at least one return statement
}