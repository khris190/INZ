#include <stdio.h>
#include "cuPrintf.cu"
#include "../include/Util/Profiler.hpp"
__global__ void fitness_v1_RGBA2(int n, int width, unsigned char *pA, unsigned char *pB, float * ret)
{   
    int i  = threadIdx.x + blockIdx.x * blockDim.x;
    if (i<n)
    {
        float absR = fabsf(pA[i*4 + 0] - pB[i*4 + 0]);
        float absG = fabsf(pA[i*4 + 1] - pB[i*4 + 1]);
        float absB = fabsf(pA[i*4 + 2] - pB[i*4 + 2]);
        float absA = fabsf(pA[i*4 + 3] - pB[i*4 + 3]);
        float val2 = (absR + absG + absB) + absA;
        ret[i] = (float)(255.f - val2 / 4.f) / 255.f;
        
    }
}


float calculateFitness(unsigned char *img_data, unsigned char *surface_data, int _width, int _height){

    unsigned char *x, *y;
    float *ret;
    // Allocate Unified Memory – accessible from CPU or GPU
    int size = _width * _height;


    cudaMallocManaged(&x, 4 * size *sizeof(unsigned char));
    cudaMallocManaged(&y, 4 * size *sizeof(unsigned char));
    cudaMallocManaged(&ret, size *sizeof(float));
    
    
    cudaMemcpy(x, img_data, 4 * _width * _height, cudaMemcpyDefault);
    cudaMemcpy(y, surface_data, 4 * _width * _height, cudaMemcpyDefault);


    fitness_v1_RGBA2 <<<_width,_height>>>(size, _width, x, y, ret);
    cudaError_t ce = cudaGetLastError();
    cudaDeviceSynchronize();
    float result = 0;
    int temp_offset;
    float row_fitness = 0;
    {
        newTimer("sumUpFitness");
        for (size_t y = 0; y < _height; y++)
        {
            for (size_t x = 0; x < _width; x++)
            {
                temp_offset = y * _width + x;
                row_fitness += ret[temp_offset];
            }
            row_fitness /= _width;
            result += row_fitness;
            row_fitness = 0;
        }
        result /= _height;
    }

    // Free memory
    cudaFree(x);
    cudaFree(y);
    cudaFree(ret);
    return (result);
}