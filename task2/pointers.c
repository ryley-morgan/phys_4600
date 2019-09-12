#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int x;
    int y;
    int* p; //<-store pointer address as an integer (the type has to match the type of variable stored at this memory address)

    x = 5;
    y = 7;
    p = &x; // & indicates store address of value assigned to variable x

    printf("x=%d\ny=%d\np=%p",x,y,p);

    printf('\n*p=%',*p);

    *p += 2; // add 2 to the value of the variable stored in the memory address that p is pointing to

    printf("x=%d\ny=%d\np=%p",x,y,p);

    p += 2; //this adds two to  the value of the address that is stored in P (increments )

    printf("x=%d\ny=%d\np=%p",x,y,p);


    /* The benefit of pointers come from their use in array's and functions */

    printf("ARRAYS:");

    int array [] = {12,14,16,18};

    // array <-pointer to the memory address of the first element in the array

    for (int i = 0; i < 4; ++i)
    {
        printf("\n%d", array[i]);
    }

    printf("using cursors"); // This is considerably faster than the ARRAYS method above in the for-loop

    int* cursor = array;

    for (int i = 0; i < 4; ++i)
    {
        printf("\n%d", *cursor);

        cursor ++; //Knows that it is an integer so when you say plus one, it says plus 4 bytes to the integer memory address

    }
}