INC := -I${CUDA_HOME}/include
LIB := -L${CUDA_HOME}/lib64 -lcudart -lcuda -lcublas -lcurand

GCC = g++
NVCC = ${CUDA_HOME}/bin/nvcc

NVCCFLAGS = -O3 -arch=sm_35 --ptxas-options=-v -Xcompiler -Wextra -lineinfo

GCC_OPTS =-O3 -Wall -Wextra $(INC)

EXCFILE = reduction


all: clean compile reduction_omp reduction

compile: Makefile
	$(NVCC) -o $(EXCFILE) reduction.cu $(LIB) $(NVCCFLAGS) 

clean:	
	rm -f *.o $(ANALYZE)

#serial compiler
CC  = gcc

# MPI compiler wrapper
MPI_CC = mpicc

# flags
CFLAGS = -O3 -mavx -std=c99 -Wall -Wextra -pedantic
CFLAGS_OMP = -fopenmp

# libraries
LIBS = -lm

reduction_omp:	reduction_omp.o
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -o reduction_omp reduction_omp.o $(LIBS)

reduction_omp.o:	reduction_omp.c
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -c reduction_omp.c
