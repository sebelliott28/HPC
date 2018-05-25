INC     := -I$(CUDA_HOME)/include -I.
LIB     := -L$(CUDA_HOME)/lib64 -lcudart -lcublas -lcufft

NVCCFLAGS	:= -lineinfo -arch=sm_35 --ptxas-options=-v --use_fast_math

all:		cuRAND

cuRAND:		cuRAND.cu Makefile
                nvcc cuRAND.cu -o cuRAND $(INC) $(NVCCFLAGS) $(LIB)

