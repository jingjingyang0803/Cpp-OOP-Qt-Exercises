#include "rectangle.hh"
#include <iostream>

Rectangle::Rectangle(char color, double width, double height)
    : Shape(color), width_(width), height_(height)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::area(std::ostream& output) const
{
    output << "Area: " << width_ * height_ << std::endl;
}

void Rectangle::circumference(std::ostream& output) const
{
    output << "Circumference: " << 2 * (width_ + height_) << std::endl;
}

void Rectangle::print(std::ostream& output) const
{
    get_color(output);
    output << " rectangle with width " << width_ << " and height " << height_ << std::endl;
    area(output);
    circumference(output);
}
