#include <time.h>

srand(time());  // max rand based on current system time
int i = rand();

int i = rand()%10; // for numbers between 0-10

// Note: adding two random numbers will give you a binomial distribution.

float r1 = (float)rand()/(float)RAND_MAX;
float r2 = (float)rand()/(float)RAND_MAX;

float perturbation = r1-r2/1000;
//to get a small number: r1-r2/1000