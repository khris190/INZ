#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "fitness.hpp"
#include "Util/Profiler.hpp"
#include <stdlib.h>
#include <random>
//#include "CImg.h"
#include <cairo/cairo.h>
#include<thread>

#pragma region floats

struct float2
{
    float x, y;
    float2(float x_ = 0, float y_ = 0);
};
struct float3
{
    float x, y, z;
    float3(float x_ = 0, float y_ = 0, float z_ = 0);
};
struct float4
{
    float x, y, z, a;
    float4(float x_ = 0, float y_ = 0, float z_ = 0, float a_ = 0);
};

#pragma endregion floats

struct point
{
    float x, y;
    void offset(float x_, float y_)
    {
        x += x_;
        y += y_;
    }
};

point rotate(float x, float y, float angle);

void drawRectangle(cairo_surface_t *surface, int x, int y, float scaleX, float scaleY, float rotation, unsigned char color[3]);

float fRand();

struct Gene
{
    short typeOfShape;
    float2 position;
    float rotation;
    float2 scale;
    float4 color;
    void createRandom();
    void mutate(float mutation_rate = 0.001);
    void mutate_color(float mutation_rate = 0.001);
    void mutate_pos(float mutation_rate = 0.001);
    void mutate_rot(float mutation_rate = 0.001);
    void mutate_size(float mutation_rate = 0.001);
    void wiggle(float mutation_rate = 0.001);
    void wiggle_color(float mutation_rate = 0.001);
    void wiggle_pos(float mutation_rate = 0.001);
    void wiggle_rot(float mutation_rate = 0.001);
    void wiggle_size(float mutation_rate = 0.001);

};

struct Genotype
{
    int size;
    Gene *GeneArr;
    Genotype(int size_ = 64);
    void mutate(float mutation_rate = 0.001);
    void wiggle(float mutation_rate = 0.001);
    void cross(Genotype *parent1_, Genotype *parent2_, float mutation_rate = 0.05f, bool doCross = true);
    void Draw(cairo_surface_t *img);
    ~Genotype();
};

class artGeneration
{
private:
    Genotype **children;
    int children_size;
    int parent1, parent2;

    void makeChildren(float mutation_rate = 0.05f,bool doCross = true);

    void generateFirstPopulation(int children_size, int genotype_size);

public:
    artGeneration(int children_size = 50, int genotype_size = 64);
    void Draw(cairo_surface_t *img, size_t index);
    int fitnessPopulation(cairo_surface_t *img, float simmilarity = 0.8f);
    ~artGeneration();
};

#endif // ARTGENERATION_HPP
