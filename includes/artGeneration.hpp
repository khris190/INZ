#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "fitness.hpp"
#include "Util/Profiler.hpp"
#include <stdlib.h>
#include <cairo/cairo.h>
#include <thread>
#include "Genes/Genotype.hpp"


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
