#include "Gene.hpp"
#include "Randoms.hpp"
#include <math.h>

shape_type genType()
{
    unsigned char out;
    // reroll while we get stuff that is not turned on
    do
    {
        out = (1 << rand() % Config::shape_types_amount);
    } while ((out & Config::Shape_types.value.shapes) == 0);

    return (shape_type)out;
}

void Gene::createRandom()
{
    typeOfShape = genType();
    position = myData::float2(fRand(), fRand());
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::mutate(float mutation_rate)
{
    if (Config::enabled_shape_types_amount > 1)
    {
        mutate_type(mutation_rate);
    }

    mutate_color(mutation_rate);
    mutate_pos(mutation_rate);
    mutate_rot(mutation_rate);
    mutate_size(mutation_rate);
}
void Gene::mutate_type(float mutation_rate)
{

    if (fRand() <= mutation_rate / 2)
    {
        typeOfShape = genType();
    }
}
void Gene::mutate_color(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
    }
}
void Gene::mutate_pos(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        position = myData::float2(fRand(), fRand());
    }
}
void Gene::mutate_rot(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        rotation = fRand();
    }
}
void Gene::mutate_size(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        scale = myData::float2(fRand(), fRand());
    }
}

void Gene::wiggle(float mutation_rate)
{
    wiggle_color(mutation_rate);
    wiggle_pos(mutation_rate);
    wiggle_rot(mutation_rate);
    wiggle_size(mutation_rate);
}

void Gene::wiggle_color(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        color.r += (fRand() - color.r) / 50;
        color.g += (fRand() - color.g) / 50;
        color.b += (fRand() - color.b) / 50;
        color.a += (fRand() - color.a) / 50;
    }
}
void Gene::wiggle_pos(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        position.x += (fRand() - position.x) / 100;
        position.y += (fRand() - position.y) / 100;
    }
}
void Gene::wiggle_rot(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        rotation += (fRand() - rotation) / 50;
    }
}
void Gene::wiggle_size(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        scale.x += (fRand() - scale.x) / 50;
        scale.y += (fRand() - scale.y) / 50;
    }
}