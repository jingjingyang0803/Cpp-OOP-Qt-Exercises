#include "circle.hh"

#include <cmath>
#include <iostream>

const double PI = 3.14159;

Circle::Circle(char color, double radius) : Shape(color)
{
    radius_ = radius;
}

Circle::~Circle()
{
}

void Circle::area(std::ostream& output) const
{
    output << "Area: " << PI * radius_ * radius_ << std::endl;
}

void Circle::circumference(std::ostream& output) const
{
    output << "Circumference: " << 2 * PI * radius_ << std::endl;
}

void Circle::print(std::ostream& output) const
{
    get_color(output);
    output << " circle with radius " << radius_ << std::endl;
    area(output);
    circumference(output);
}