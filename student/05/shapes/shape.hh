#ifndef SHAPE_HH
#define SHAPE_HH

#include <map>
#include <string>

using namespace std;

enum class Color
{
    RED,
    BLUE,
    YELLOW,
    GREEN
};

const map<char, Color> COLOR_CODES = {
    {'r', Color::RED},    {'R', Color::RED},    {'b', Color::BLUE},  {'B', Color::BLUE},
    {'y', Color::YELLOW}, {'Y', Color::YELLOW}, {'g', Color::GREEN}, {'G', Color::GREEN}};

const map<Color, string> COLOR_NAMES = {
    {Color::RED, "Red"}, {Color::BLUE, "Blue"}, {Color::YELLOW, "Yellow"}, {Color::GREEN, "Green"}};

class Shape
{
  public:
    Shape(char color);
    virtual ~Shape();
    void paint(char color);

    // Add missing functions
    void get_color(std::ostream& output) const;
    virtual void area(std::ostream& output) const = 0;
    virtual void circumference(std::ostream& output) const = 0;
    virtual void print(std::ostream& output) const = 0;

  private:
    Color color_;
};

#endif // SHAPE_HH
