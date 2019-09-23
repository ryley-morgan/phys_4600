#include <stdio.h>
#include <stdlib.h>

int int main()
{
    char letter = '9'; //This letter contains the ascii value that means 9
    char* words = "Hello world"; //c-compiler automatically puts an extra character at the end of this array '\0' (null terminated string)
    char* cursor = words;

    while(*cursor != '\0')
    {
        printf("%c",*cursor);
        cursor++;
    }

    char* string = "This is a int = %d float = %0.2f char = %c "; //string literal - best when using it a lot in a program because it saves memory
    int x =5;
    float y = 3.1415;
    char a = 'a';
    printf(string,x,y,a);

    char a = 'a';
    float inputx;

    scanf("%f",&inputx); //stop and wait for input
    printf("\nThis is was %f", inputx);


    int correct = scanf("%f",&inputx)

    fflush(stdout); //flushing printf output
    fflush(stdin);  //flushing scanf input
    /*
    printf/scanf    to/from-console(stdout/stdin)
    sprintf/sscanf  to/from-string
    */
    char a[65];
    char b = "Number %f";
    sprintf(a,b,x); //copy from one string to another

    char c = "2.74 1.87";
    sscanf(c,"%f %f",&x,&y); //pull numbers out of a string and put into two variables

    /*
    viprintf/viscanf used to send information to and from instruments
    fprintf/fscanf  to and from files
    */
    
    return 0;
}