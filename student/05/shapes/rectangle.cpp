#include "rectangle.hh"
#include <iostream>

Rectangle::Rectangle(char color, double width, double height)
    : Shape(color), width_(width), height_(height)
{
}

Rectangle::~Rectangle()
{
}

double Rectangle::area() const
{
    return width_ * height_;
}

double Rectangle::circumference() const
{
    return 2 * (width_ + height_);
}

void Rectangle::print(std::ostream& output) const
{
    output << COLOR_NAMES.at(get_color());
    output << " rectangle with width " << width_ << " and height " << height_ << std::endl;
    output << "Area: " << area() << std::endl;
    output << "Circumference: " << circumference() << std::endl;
}
