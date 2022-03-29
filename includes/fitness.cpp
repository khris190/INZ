
#include "fitness.hpp"


float fitness_v1(unsigned char &pA, unsigned char &pB)
{
    return (float)(255 - std::abs(pA - pB)) / 255.f;
}

float fitness(cimg_library::CImg<unsigned char> &img, cimg_library::CImg<unsigned char> &generated)
{
    int temp_offset;
    int offset = img._width * img._height;
    float tmp_fitness = 0, row_fitness = 0, img_fitness = 0;
    for (size_t y = 0; y < img._height; y++)
    {
        for (size_t x = 0; x < img._width; x++)
        {
            temp_offset = y * img._width + x;

            tmp_fitness += fitness_v1(img._data[temp_offset], generated._data[temp_offset]);
            tmp_fitness += fitness_v1(img._data[temp_offset + offset], generated._data[temp_offset + offset]);
            tmp_fitness += fitness_v1(img._data[temp_offset + offset * 2], generated._data[temp_offset + offset * 2]);
            tmp_fitness /= 3.f;
            row_fitness += tmp_fitness;
            tmp_fitness = 0;
        }
        row_fitness /= img._width;
        img_fitness += row_fitness;
        row_fitness = 0;
    }
    img_fitness /= img._height;
    return img_fitness;
}