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

double Circle::area() const
{
    return PI * radius_ * radius_;
}

double Circle::circumference() const
{
    return 2 * PI * radius_;
}

void Circle::print(std::ostream& output) const
{
    get_color(output);
    output << " circle with radius " << radius_ << std::endl;
    output << "Area: " << area() << std::endl;
    output << "Circumference: " << circumference() << std::endl;
}