#include "DataStructures.hpp"

float2::float2(float x_, float y_)
    : x(x_),
      y(y_)
{
    
}

float3::float3(float x_, float y_, float z_)
    : x(x_),
      y(y_),
      z(z_)
{
    
}

float4::float4(float x_, float y_, float z_, float a_)
    : x(x_),
      y(y_),
      z(z_),
      a(a_)
{
    
}

position_2D::position_2D(float x_, float y_)
    : x(x_),
      y(y_)
{
    
}

void position_2D::move(float x_, float y_) {
    this->x += x_;
    this->y += y_;
}

color_RGBA::color_RGBA(float r_, float g_, float b_, float a_)
    : r(r_),
      g(g_),
      b(b_),
      a(a_)
{
    
}

color_RGB::color_RGB(float r_, float g_, float b_)
    : r(r_),
      g(g_),
      b(b_)
{
    
}
