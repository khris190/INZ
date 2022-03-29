
#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <cstdlib>
#include "CImg.h"


float fitness_v1(unsigned char &pA, unsigned char &pB);
float fitness(cimg_library::CImg<unsigned char> &img, cimg_library::CImg<unsigned char> &generated);

#endif // FITNESS_HPP
