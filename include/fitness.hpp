
#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <cstdlib>
//#include "CImg.h"
#include <cairo/cairo.h>
#include "Util/Profiler.hpp"
#include "Util/Logger.hpp"

//float3 test;

float fitness_v1_RGBA(unsigned char *pA, unsigned char *pB);
float fitness(cairo_surface_t *img, cairo_surface_t *surface);

#endif // FITNESS_HPP
