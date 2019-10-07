#ifndef __FILTERS_H
#define __FILTERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int movingAverageFilter(double* data, int data_size, const char* window_size, double* output_data);
#endif