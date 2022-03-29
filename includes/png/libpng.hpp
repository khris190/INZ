#ifndef LIBPNG_HPP
#define LIBPNG_HPP

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "../artGeneration.hpp"

#ifndef cimg_use_png
#define cimg_use_png
#endif
#include "CImg.h"

// my part
#pragma region MyPart


class Picture
{
public:
    cimg_library::CImg<unsigned char> image;
public:
    int getHeight();
    int getWidth();
    int getDepth();
    void write_png_file(char *file_name);
    Picture(char *file_name);
    int getMaxPixelVal();
    ~Picture();
};

#pragma endregion MyPart

#endif // LIBPNG_HPP
