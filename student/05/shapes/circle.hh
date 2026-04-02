#ifndef CIRCLE_HH
#define CIRCLE_HH

#include "shape.hh"

class Circle : public Shape
{

  public:
    Circle(char color, double radius);
    ~Circle();
    double area(std::ostream& output) const override;
    double circumference(std::ostream& output) const override;
    void print(std::ostream& output) const override;

  private:
    double radius_;
};

#endif // CIRCLE_HH