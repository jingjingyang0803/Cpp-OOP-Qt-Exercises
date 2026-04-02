#include "rectangle.hh"
#include <iostream>

Rectangle::Rectangle(char color, double width, double height)
    : Shape(color), width_(width), height_(height)
{
}

Rectangle::~Rectangle()
{
}

double Rectangle::area(std::ostream& output) const
{
    return width_ * height_;
}

double Rectangle::circumference(std::ostream& output) const
{
    return 2 * (width_ + height_);
}

void Rectangle::print(std::ostream& output) const
{
    get_color(output);
    output << " rectangle with width " << width_ << " and height " << height_ << std::endl;
    output << "Area: " << area(output) << std::endl;
    output << "Circumference: " << circumference(output) << std::endl;
}
