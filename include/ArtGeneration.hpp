#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "fitness.hpp"
#include "Util/Logger.hpp"
#include "Util/Profiler.hpp"
#include <stdlib.h>
#include <cairo/cairo.h>
#include <thread>
#include "Genes/Genotype.hpp"
#include "Config/Config.hpp"
#include "Util/BS_thread_pool_light.hpp"

class ArtGeneration
{
private:
    Genotype **children_;
    int children_size_;
    int parent1_, parent2_;

    void CreateChildren(float mutation_rate = 0.05f);
    void GenerateFirstPopulation(int children_size, int genotype_size);
    void Draw(cairo_surface_t *img, size_t index);
    static void AsyncFitness(cairo_surface_t *img, Genotype **children, volatile int *best_indexes, volatile float *best_scores, int start, int stop, int _width, int _height);

public:
    ArtGeneration(int children_size = 50, int genotype_size = 64);
    void StartEvolution(cairo_surface_t *img);
    ~ArtGeneration();
};

#endif // ARTGENERATION_HPP