
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <cuda.h>
#include <curand.h>
#include <sys/time.h>

#define MILLION 1000000.0

#define NUM_ELS 1024

__global__ void reduction(int num_els, float *d_input, float *d_output)
{
    // Allocate shared memory

    __shared__  float smem_array[NUM_ELS];

    //reset d_output to 0

    d_output[0] = 0;

    //define local thread id for each block, and input index across all blocks

    int tid = threadIdx.x;
    int index = blockIdx.x*blockDim.x + threadIdx.x;

    // first, each thread loads data into shared memory

    if (index < num_els) {
    	smem_array[tid] = d_input[index];
    }
    else smem_array[tid] =0;

    // next, we perform binary tree reduction

    for (int d = blockDim.x/2; d > 0; d /= 2) {
      __syncthreads();  // ensure previous step completed 
      if (tid<d)  smem_array[tid] += smem_array[tid+d];
    }

    // finally, first thread in each block puts result into global memory
    
    if (tid == 0) atomicAdd(&d_output[0], smem_array[0]);
}


// wall_clock_time - wall clock time function 

double wall_clock_time (void) {

  double secs;
  struct timeval tp;

  gettimeofday (&tp,NULL);
  secs = (MILLION * (double) tp.tv_sec + (double) tp.tv_usec) / MILLION;
  return secs;

}


////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

int main( int argc, const char** argv) 
{
    int num_els, num_threads, mem_size, nblocks;

    float *h_data;
    float *d_input, *d_output;
 
    double start, finish;

   //Prompt user to enter number of numbers to work with
    printf("Enter the number of random numbers to work with:\t");
    scanf("%d", &num_els);

    // initialise card

    num_threads = NUM_ELS;
    mem_size    = sizeof(float) * num_els;


    // allocate device memory input and output arrays, and host memory

    cudaMalloc((void**)&d_input, mem_size);
    cudaMalloc((void**)&d_output, sizeof(float));
    h_data = (float*) malloc(mem_size);

    // now need to generate random numbers into d_input using cuRAND library
    
    // initiate random number generator
    curandGenerator_t gen;

    curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);

    // Set the generator options
    curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);

    // create random numbers, initialized to h_data, with mean 500 & standard deviation 200 
    curandGenerateNormal(gen, d_input, num_els, 500.0f, 50.0f);

    // execute the kernel

    nblocks = num_els/NUM_ELS + (num_els % NUM_ELS == 0 ? 0 : 1); //effective ceiling function to calculate number of blocks required
    printf("nblocks = %d\n", nblocks); //check here

    start = wall_clock_time (); 

    reduction<<<nblocks,num_threads>>>(num_els, d_input,d_output);

    finish = wall_clock_time ();

    // copy result from device to host

    cudaMemcpy(h_data, d_output, sizeof(float), cudaMemcpyDeviceToHost);

    // check results

    printf("reduction error = %f\n",h_data[0]/num_els);
    printf("process time = %e s\n", finish - start);

    // cleanup memory

    free(h_data);
    cudaFree(d_input);
    cudaFree(d_output);

    // CUDA exit -- needed to flush printf write buffer

    cudaDeviceReset();
}
