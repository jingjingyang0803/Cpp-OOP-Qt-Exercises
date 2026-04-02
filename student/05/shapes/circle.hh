#ifndef CIRCLE_HH
#define CIRCLE_HH

#include "shape.hh"

class Circle : public Shape
{

  public:
    Circle(char color, double radius);
    ~Circle();
    void area(std::ostream& output) const override;
    void circumference(std::ostream& output) const override;
    void print(std::ostream& output) const override;

  private:
    double radius_;
};

#endif // CIRCLE_HH