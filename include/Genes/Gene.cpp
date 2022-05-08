#include "Gene.hpp"
#include "Randoms.hpp"

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
    position = myData::position_2D(fRand(), fRand());
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
        position = myData::position_2D(fRand(), fRand());
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
        color.r += (fRand() * 2 - 1) / 100;
        color.g += (fRand() * 2 - 1) / 100;
        color.b += (fRand() * 2 - 1) / 100;
        color.a += (fRand() * 2 - 1) / 100;
    }
}
void Gene::wiggle_pos(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        position.x += (fRand() * 2 - 1) / 200;
        position.y += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_rot(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        rotation += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_size(float mutation_rate)
{
    if (fRand() <= mutation_rate)
    {
        scale.x += (fRand() * 2 - 1) / 200;
        scale.y += (fRand() * 2 - 1) / 200;
    }
}
