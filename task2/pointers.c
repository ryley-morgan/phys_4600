#include <stdio.h>
#include <math.h>

int main(){
    int x;
    int y;
    int* p; //<-store pointer address as an integer

    x = 5;
    y = 7;
    p = &x; // & indicates store address of value assigned to variable x

    printf("x=%d\ny=%d\np=%p",x,y,p);

    printf('\n*p=%',*p);

    *p += 2; // add 2 to the value of the variable stored in the memory address that p is pointing to

    printf("x=%d\ny=%d\np=%p",x,y,p);

    p += 2; //this adds two to  the value of the address that is stored in P (increments )

    printf("x=%d\ny=%d\np=%p",x,y,p);

}