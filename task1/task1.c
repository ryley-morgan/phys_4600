#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
File: task0.1.c
Author: Ryley Morgan <ryley.morgan@email.kpu.ca>
*/
int main() {
    /* main() prints "Hello, world!" to the terminal */ 
    
    float angle;
    float hypot = 12;
    angle = 0.7;

    float opp;

    opp = hypot * sin( angle );

    printf("Opposite side = %f cm", opp);
    return 0;
}