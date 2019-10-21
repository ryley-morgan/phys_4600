#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) //argument-count, argument-values
{ 
    for (int i = 0; i < argc; ++i)
    {
        printf("\n%s",argv[i]);
    }

    FILE* inputfile;

    if(argc <2){

    }

    inputfile = fopen(argv[1]);




    return 0;
}