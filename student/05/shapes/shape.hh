#ifndef SHAPE_HH
#define SHAPE_HH

#include <string>
#include <map>

using namespace std;

enum class Color{RED, BLUE, YELLOW, GREEN};

const map<char, Color> COLOR_CODES = {{'r', Color::RED},
                                      {'R', Color::RED},
                                      {'b', Color::BLUE},
                                      {'B', Color::BLUE},
                                      {'y', Color::YELLOW},
                                      {'Y', Color::YELLOW},
                                      {'g', Color::GREEN},
                                      {'G', Color::GREEN}};

const map<Color, string> COLOR_NAMES = {{Color::RED, "Red"},
                                        {Color::BLUE, "Blue"},
                                        {Color::YELLOW, "Yellow"},
                                        {Color::GREEN, "Green"}};

class Shape
{
public:
    Shape(char color);
    virtual ~Shape();
    void paint(char color);

    // TODO Add missing functions here

private:
    Color color_;
};

#endif // SHAPE_HH

