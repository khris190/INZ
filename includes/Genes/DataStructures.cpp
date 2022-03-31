#include "DataStructures.hpp"

float2::float2(float x_, float y_)
    : x(),
      y()
{
    
}

float3::float3(float x_, float y_, float z_)
    : x(),
      y(),
      z()
{
    
}

float4::float4(float x_, float y_, float z_, float a_)
    : x(),
      y(),
      z(),
      a()
{
    
}

position_2D::position_2D(float x_, float y_)
    : x(),
      y()
{
    
}

void position_2D::move(float x_, float y_) {
    this->x += x_;
    this->y += y_;
}

color_RGBA::color_RGBA(float r_, float g_, float b_, float a_)
    : r(),
      g(),
      b(),
      a()
{
    
}

color_RGB::color_RGB(float r_, float g_, float b_)
    : r(),
      g(),
      b()
{
    
}
