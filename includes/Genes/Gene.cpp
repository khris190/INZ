#include "Gene.hpp"
#include "Randoms.hpp"


void Gene::createRandom()
{
    // typeOfShape = rand() % 2;
    typeOfShape = (shape_type)0;
    position = position_2D(fRand(), fRand());
    rotation = fRand();
    scale = float2(fRand(), fRand());
    color = color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::mutate(float mutation_rate)
{
    // mutate_type(mutation_rate);
    mutate_color(mutation_rate);
    mutate_pos(mutation_rate);
    mutate_rot(mutation_rate);
    mutate_size(mutation_rate);
}
void Gene::mutate_type(float mutation_rate)
{

    if (fRand() < mutation_rate / 2)
    {
        typeOfShape = (shape_type)(rand() % 2);
    }
}
void Gene::mutate_color(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        color = color_RGBA(fRand(), fRand(), fRand(), fRand());
    }
}
void Gene::mutate_pos(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        position = position_2D(fRand(), fRand());
    }
}
void Gene::mutate_rot(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        rotation = fRand();
    }
}
void Gene::mutate_size(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        scale = float2(fRand(), fRand());
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
    if (fRand() < mutation_rate)
    {
        color.r += (fRand() * 2 - 1) / 100;
        color.g += (fRand() * 2 - 1) / 100;
        color.b += (fRand() * 2 - 1) / 100;
        color.a += (fRand() * 2 - 1) / 100;
    }
}
void Gene::wiggle_pos(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        position.x += (fRand() * 2 - 1) / 200;
        position.y += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_rot(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        rotation += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_size(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        scale.x += (fRand() * 2 - 1) / 200;
        scale.y += (fRand() * 2 - 1) / 200;
    }
}
