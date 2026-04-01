#include "shape.hh"
#include <iostream>

Shape::Shape(char color)
{
    paint(color);
}

Shape::~Shape()
{

}

void Shape::paint(char color)
{
    if(COLOR_CODES.find(color) == COLOR_CODES.end())
    {
        cout << "Wrong color" << endl;
    }
    for(auto color_code : COLOR_CODES)
    {
        if(color_code.first == color)
        {
            color_ = color_code.second;
        }
    }
}


