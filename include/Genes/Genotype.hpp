#ifndef GENOTYPE_HPP
#define GENOTYPE_HPP

#include "Gene.hpp"
#include <cairo/cairo.h>
#include <stdlib.h>
#include <tgmath.h>
#include "Randoms.hpp"


#include <vector>
#include "../OpenGL/Drawers/mesh.hpp"
#include "../OpenGL/engine.hpp"


struct Genotype
{
    int size;
    Gene *GeneArr;
    Genotype(int size_ = 64);
    void Swap_random(float mutation_rate = 0.001);
    void mutate(float mutation_rate = 0.001);
    void wiggle(float mutation_rate = 0.001);
    void cross(Genotype *parent1_, Genotype *parent2_, float mutation_rate = 0.05f, bool doCross = true);
    void Draw(cairo_surface_t *img, float Scale = 0.5);
    ~Genotype();
};

#endif // GENOTYPE_HPP
