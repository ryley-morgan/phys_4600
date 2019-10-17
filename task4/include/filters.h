#ifndef __FILTERS_H
#define __FILTERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int movingAverageFilter(double* data, int data_size, int window_size, double* output_data);
#endif