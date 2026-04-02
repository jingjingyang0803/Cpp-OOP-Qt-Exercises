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

double Circle::area(std::ostream& output) const
{
    return PI * radius_ * radius_;
}

double Circle::circumference(std::ostream& output) const
{
    return 2 * PI * radius_;
}

void Circle::print(std::ostream& output) const
{
    get_color(output);
    output << " circle with radius " << radius_ << std::endl;
    output << "Area: " << area(output) << std::endl;
    output << "Circumference: " << circumference(output) << std::endl;
}