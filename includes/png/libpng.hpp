/*
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */
#ifndef LIBPNG_HPP
#define LIBPNG_HPP

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <libpng16/png.h>
#pragma region internetPart

void abort_(const char *s, ...);
extern int x, y;
extern int width, height;

extern png_byte color_type;
extern png_byte bit_depth;
extern png_structp png_ptr;
extern png_infop info_ptr;

extern int number_of_passes;
extern png_bytep *row_pointers;

void read_png_file(char *file_name);

void write_png_file(char *file_name);

void process_file(void);
#pragma endregion
// my part
#pragma region MyPart
struct pngData
{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;

    ~pngData()
    {
        if (row_pointers)
        {
            for (size_t i = 0; i < height; i++)
            {
                free(row_pointers[i]);
            }
            free(row_pointers);
        }
    }
};

pngData read_ARGB_png_file(char *file_name);
 
struct pixel
{
    int R, G, B, A;
};

class picture
{
private:
    int width, height;
    pixel **pixels;
    short bit_depth;

public:
    picture(pngData png);
    int getMaxPixelVal();
    ~picture();
};

#pragma endregion MyPart

#endif // LIBPNG_HPP
