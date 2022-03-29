#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "fitness.hpp"
#include "Util/Profiler.hpp"
#include <stdlib.h>
#include <random>
#include "CImg.h"

#pragma region floats

struct float2
{
    float x,y;
    float2(float x_ = 0,float y_ = 0);
};
struct float3
{
    float x,y,z;
    float3(float x_ = 0,float y_ = 0, float z_ = 0);
};
struct float4
{
    float x,y,z,a;
    float4(float x_ = 0,float y_ = 0, float z_ = 0, float a_ = 0);
};

#pragma endregion floats

struct point
{
    float x,y;
    void offset(float x_, float y_){
        x += x_;
        y += y_;
    }
};

point rotate(float x, float y, float angle);

void drawRectangle(cimg_library::CImg<unsigned char> &renderer, int x, int y, float scaleX, float scaleY, float rotation, unsigned char color[3]);

int mixCanvas(cimg_library::CImg<unsigned char> &renderer, cimg_library::CImg<unsigned char> &overlay);
int mixCanvasRGBwithRGBA(cimg_library::CImg<unsigned char> &renderer, cimg_library::CImg<unsigned char> &overlay, unsigned char color[4]);


void mixPixels(unsigned char* pixelA, unsigned char* pixelB, float mixAlpha);
float fRand();


struct Gene
{
    float2 position;
    float rotation;
    float2 scale;
    float4 color;
    void createRandom();
    void mutate(float mutation_rate = 0.001);
};

struct Genotype{
    int size;
    Gene *GeneArr;
    Genotype(int size_ = 64);
    void mutate(float mutation_rate = 0.001);
    Genotype* cross(Genotype *parent1_, Genotype *parent2_);
    void Draw( cimg_library::CImg<unsigned char> &img);
    ~Genotype();
};

class artGeneration
{
private:
    Genotype** children;
    int children_size;
    int parent1, parent2;

    Genotype makeChildren();

    void generateFirstPopulation(int children_size, int genotype_size);
public:
    artGeneration(int children_size = 50, int genotype_size = 64);
    void Draw(cimg_library::CImg<unsigned char> &img, size_t index);
    int fitnessPopulation( cimg_library::CImg<unsigned char> &img);
    ~artGeneration();

};


#endif // ARTGENERATION_HPP
