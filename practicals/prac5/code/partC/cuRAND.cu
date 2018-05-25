//random number generation

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <curand.h>

int main ( void ) {

//Allocate pointers for host and device memory
float *h_input, *h_output;
float *d_input, *d_output;

//malloc() host memory on local RAM
h_input = (float*) malloc(mem_size);
h_output = (float*) malloc(mem_size);

//allocate device memory input and output arrays
cudaMalloc( (void**) &d_input, mem_size);
cudaMalloc( (void**) &d_output, mem_size);

cudaMemcpy(d_input, h_input, mem_size, cudaMemcpyHostToDevice);

//Declare random variable
curandGenerator_t gen;

//Create random number generator 
curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);

//Set generator options
curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);

//Generator random numbers
curandGenerateNormal (gen, d_input, NUM_ELS, 0.0f, 1.0f); 

cudaMemcpy(h_output, d_output, mem_size, cudaMemcpyDeviceToHost);

//Cleanup memory

free(h_input);
free(h_output);
cudaFree(d_input);
cudaFree(d_output);

}

