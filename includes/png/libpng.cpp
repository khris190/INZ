#include "libpng.hpp"

// my part

/* create file */
int Picture::getHeight()
{
    return image._height;
}
int Picture::getWidth()
{
    return image._width;
}
int Picture::getDepth()
{
    return image._depth * 8;
}

Picture::Picture(char *file_name)
{
    newTimer("Opening ");
    cimg_library::CImg<unsigned char> img(file_name);
    this->image = img;
    //cimg_library::CImg<unsigned char> render(img.width(), img.height(), 1, 3, 255);
    //artGeneration test(32, 64);
    //test.Draw(render);
    //render.save((char*)"saveRenderTest.jpg");
    //render.display();
}
int Picture::getMaxPixelVal()
{
    int ret = 2;
    ret << image._depth * 8;
    return ret - 1;
}

Picture::~Picture()
{
}
