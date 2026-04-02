#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include "shape.hh"

class Rectangle : public Shape
{
  public:
    Rectangle(char color, double width, double height);
    ~Rectangle();

    double area(std::ostream& output) const override;
    double circumference(std::ostream& output) const override;
    void print(std::ostream& output) const override;

  private:
    double width_;
    double height_;
};

#endif // RECTANGLE_HH