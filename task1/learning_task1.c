#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
File: task1.c
Author: Ryley Morgan <ryley.morgan@email.kpu.ca>
*/
int main() {
    /* Calculating the opposite side for a fixed range of angles */ 
    
    float angle;    float hypot = 12;
    float opp[30];
    for (int i = 0; i < 30; ++i)
    {
        /* Calculate opp */
        angle = (M_PI/2) * (i/30.0);
        opp[i] = hypot * sin(angle);
        printf("For angle = %f radians \t Opposite side = %f cm\n", angle, opp[i]);
    } 
    printf("Angle 5 = %f", opp[4]);
    return 0;
}