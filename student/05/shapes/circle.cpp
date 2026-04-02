#include "circle.hh"

#include <cmath>
#include <iostream>

Circle::Circle(char color, double radius) : Shape(color)
{
    radius_ = radius;
}

Circle::~Circle()
{
}

void Circle::area(std::ostream& output) const
{
    output << "Area: " << M_PI * radius_ * radius_ << std::endl;
}

void Circle::circumference(std::ostream& output) const
{
    output << "Circumference: " << 2 * M_PI * radius_ << std::endl;
}

void Circle::print(std::ostream& output) const
{
    get_color(output);
    output << " circle with radius " << radius_ << std::endl;
    area(output);
    circumference(output);
}