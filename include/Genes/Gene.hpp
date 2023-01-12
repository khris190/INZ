#ifndef GENE_HPP
#define GENE_HPP

#include "DataStructures.hpp"
#include "../Config/Config.hpp"
#include "..//Util/Logger.hpp"
// TODO implement parametrized shapes
struct Gene
{
    shape_type typeOfShape;
    myData::float2 position;
    float rotation;
    myData::float2 scale;
    myData::color_RGBA color;
    void createRandom();
    void mutate(float mutation_rate = 0.001);
    void mutate_type(float mutation_rate = 0.001);
    void mutate_color(float mutation_rate = 0.001);
    void mutate_pos(float mutation_rate = 0.001);
    void mutate_rot(float mutation_rate = 0.001);
    void mutate_size(float mutation_rate = 0.001);
    void wiggle(float mutation_rate = 0.001);
    void wiggle_color(float mutation_rate = 0.001);
    void wiggle_pos(float mutation_rate = 0.001);
    void wiggle_rot(float mutation_rate = 0.001);
    void wiggle_size(float mutation_rate = 0.001);
    ~Gene();
};

#endif // GENE_HPP
