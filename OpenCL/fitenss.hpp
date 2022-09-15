#include <boost/compute/cl.hpp>

float calculateFitness(unsigned char *img_data, unsigned char *surface_data, int _width, int _height){

    unsigned char *test;
    // Allocate Unified Memory – accessible from CPU or GPU
    int size = _width * _height;
    mxX.lock();
    if(x == nullptr) {
        cudaMallocManaged(&x, 4 * size *sizeof(unsigned char));
        cudaMemcpy(x, img_data, 4 * size, cudaMemcpyDefault);
    }
    mxX.unlock();
    cudaMallocManaged(&test, 4 * size *sizeof(unsigned char));
    
    
    cudaMemcpy(test, surface_data, 4 * size, cudaMemcpyDefault);

    {
        newTimer("calculate fitness_v1_RGBA2");
        fitness_v1_RGBA2 <<<_width,_height>>>(size, _width, x, test);
        cudaError_t ce = cudaGetLastError();
        cudaDeviceSynchronize();
    }
    //increasing of this number lowers calculate2 timings 2 times and increases calculateFitnessFromArray 4 times, so its important to think about those numbers
    short offset = 64;
    short rest = size% offset;
    size_t amount = (size - rest) / offset;
    size_t threadAmount = sqrt(amount) + 1;

    {
        newTimer("calculateFitnessFromArray");
        calculateFitnessFromArray<<<threadAmount, threadAmount>>>(offset, (float*)test, size);
        cudaError_t ce = cudaGetLastError();
        cudaDeviceSynchronize();
    }


    double result = 0;
    double row_fitness = 0;
    float tmp_fitness = 0;
    {
        newTimer("calculate2");
        {
            for (int i = 0; i < amount; i++)
            {
                memcpy(&tmp_fitness, (void*)(test + 4*i*offset), sizeof(float));
                row_fitness += tmp_fitness;
            }
            for (size_t i = 0;i < rest; i++)
            {
                memcpy(&tmp_fitness, (void*)(test + amount*offset*4 + i*4 ), sizeof(float));
                row_fitness += tmp_fitness;
            }
            result += row_fitness;
            row_fitness = 0;
            result /= size;
        }
    }

    // Free memory
    //cudaFree(x);
    cudaFree(test);
    //cudaFree(ret);
    return (result);
}