#include<stdio.h>
#include <stdlib.h>
  
int main(int argc,char* argv[])
{
    int counter;
    printf("Executing: %s",argv[0]);

    if(argc > 2)
    {
        for(counter=1; counter<argc; counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
            if (!atof(argv[counter])) {
                printf("\n Wrong arguments. You must enter float numbers as arguments");
                return 0;
            }
        
        float sum = 0;
        for(counter=1; counter<argc; counter++)
            sum += atof(argv[counter]);
        float average = sum / (argc - 1);
        printf("\n Average of numbers= %f \n", average); 
    }
    else {
        printf("\n Wrong input. You must provide float numbers as arguments");
    }
    return 0;
}