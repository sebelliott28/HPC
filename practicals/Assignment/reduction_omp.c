#include <stdio.h>
#include <stdlib.h>

#include "omp.h"


#define NUM_ELS 100000

int main() {
	
    float random_array[NUM_ELS];
    float sum=0;
    int i, j;

    //declare timer variables
    double start, finish;

    //generate random numbers into array 

        for(j=0; j<NUM_ELS; j++) {
            random_array[j] = ((float)rand())/((float)RAND_MAX);
        }
 

    //initialize timer for comparison with GPU

    start = omp_get_wtime(); 

#pragma omp parallel default( none ) shared(sum, random_array) private(i, j)
    {

    //use an openMP for loop to sum values of the array

    #pragma omp for reduction(+:sum)
        for(i=0; i<NUM_ELS; i++) {
            sum += random_array[i];
        }

    }    

    finish = omp_get_wtime();

    printf("Average:\t%f\n", sum/(float)NUM_ELS);
    printf("Time for CPU :%e s\n", finish - start);

    return(0);

}
