#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include <stdlib.h>
#include <random>

#pragma region floats

struct float2
{
    float x,y;
    float2(float x_,float y_){
        x = x_;
        y = y_;
    }
};
struct float3
{
    float x,y,z;
    float3(float x_,float y_, float z_){
        x = x_;
        y = y_;
        z = z_;
    }
};
struct float4
{
    float x,y,z,a;
    float4(float x_,float y_, float z_, float a_){
        x = x_;
        y = y_;
        z = z_;
        a = a_;
    }
};

#pragma endregion floats

struct Gene
{
    float2 position;
    float rotation;
    float2 scale;
    float4 color;
};

struct Genotype{
    int size;
    Gene *GeneArr;
    Genotype(int size_ = 64);
    void mutate(float mutation_rate = 0.001)
    {
        
    }
    ~Genotype();
};

class artGeneration
{
private:
    Genotype children;
    int childrenSize;
    u_short parent1, parent2;

    void generateFirstPopulation(int children_size, int genotype_size)
    {

    }
public:
    artGeneration(int children_size = 50, int genotype_size = 64)
    {
        generateFirstPopulation(children_size, genotype_size);
    }

    ~artGeneration()
    {

    }
};


#endif // ARTGENERATION_HPP
