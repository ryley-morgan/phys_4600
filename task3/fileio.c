#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * input_file;  //FILE is a placeholder that points to an actual file that is on your file
    FILE * output_file;
    float x;
    float y;

    input_file = fopen("data1.dat","r"); //Read data.dat, returns pointer to openfile

    if (input_file != NULL)
    {
        fscanf(input_file,"%f %f",&x,&y);
        printf("%f\n", y);

        fclose(input_file);
    }
    else
        printf("Failed to open file!");
    

    output_file=fopen("data.dat","w"); // Use r to read, w to write, and a to append
    fprintf(output_file,"%f %f",y,x);
    fclose(output_file);



}