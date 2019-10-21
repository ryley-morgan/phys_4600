#ifndef __STATISTICS_H      //include guard!
#define __STATISTICS_H      //include guard!

#include <stdio.h>

#define MAX_N_DATA 128;

double stdevf(double* data, int n, double*meanout);

int load_data_columns(FILE* fp, double* xdata, double* ydata, int max_n);



#endif  //include Guard!