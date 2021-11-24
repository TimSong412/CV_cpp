#include <stdio.h>
#include "cuda_runtime.h"

__global__ void square (float * d_out, float * d_in)
{
    int idx = threadIdx.x;
	float f = d_in[idx];
	d_out[idx] = f * f;
}

int main(int argc,char** argv)
{
    const int arraysize = 64;
	const int arraybytes = arraysize * sizeof(float);

	//generate the input array on the host
	float h_in[arraysize];
	for (int i = 0; i < arraysize; i++)
	{
		h_in[i] = float(i);
	}
	float h_out[arraysize];
	
	//declare GPU memory pointers
	float* d_in;
	float* d_out;

	//allocate GPU memory
	cudaMalloc((void**)&d_in, arraybytes);
	cudaMalloc((void**)&d_out, arraybytes);

	//transfer the array to GPU 
	cudaMemcpy(d_in, h_in, arraybytes, cudaMemcpyHostToDevice);

	//launch the kernel
	square << <1, arraysize >> > (d_out, d_in);//1-thread blocks ;arraysize-threads
	
	//copy the result array back to the CPU
	cudaMemcpy(h_out, d_out, arraybytes, cudaMemcpyDeviceToHost);

	//print out the resulting array
	for (int i = 0; i < arraysize; i++)
	{
		printf("%f", h_out[i]);
		printf(((i % 4) != 3) ? "\t" : "\n");
	}

    //free GPU memory allocation
    cudaFree(d_in);
    cudaFree(d_out);
    
    return 0;
}