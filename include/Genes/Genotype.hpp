#ifndef GENOTYPE_HPP
#define GENOTYPE_HPP

#include "Gene.hpp"
#include <cairo/cairo.h>
#include <stdlib.h>
#include <tgmath.h>
#include "Randoms.hpp"
struct Genotype
{
    int size;
    Gene *GeneArr;
    Genotype(int size_ = 64);
    void Swap_all(float mutation_rate = 0.001f);
    void Swap_one(float mutation_rate = 0.001f, int i = -1);
    void mutate(float mutation_rate = 0.001f);
    void wiggle(float mutation_rate = 0.001f);
    void cross(Genotype *parent1_, Genotype *parent2_);
    void Draw(cairo_surface_t *img, float Scale = 0.5);
    ~Genotype();
};

#endif // GENOTYPE_HPP
