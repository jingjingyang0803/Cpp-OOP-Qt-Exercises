#include "circle.hh"
#include "rectangle.hh"
#include "shape.hh"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Splits the given string into several strings, by using the given delimiter
// as a separator.
// Returns the splitted string as a vector such that each string part is an
// element of the vector.
// User can specify if empty parts will be ignored or not.
vector<string> split(const string& str, const char delimiter, bool ignore_empty = false)
{
    vector<string> result;
    string tmp = str;

    while (tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (not(ignore_empty and word.empty()))
        {
            result.push_back(word);
        }
    }
    if (not(ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Goes through the given vector of Shapes and prints each element
// (by calling their print functions).
void print_shapes(vector<shared_ptr<Shape>> shapes)
{
    int n = 1;
    for (const auto& shape : shapes)
    {
        cout << "\nShape " << n << ":" << endl;
        shape->print(cout);
        n++;
    }
}

int main()
{
    cout << "Enter file name: ";
    string file_name = "";
    getline(cin, file_name);
    ifstream file(file_name);
    if (not file)
    {
        cout << "File not found" << endl;
        return EXIT_FAILURE;
    }
    string line = "";

    vector<shared_ptr<Shape>> shapes;

    // Goes through the input file line by line and splits each line.
    // Based on the content of each line, creates either a Circle
    // or a Rectangle, and pushes the shape to the vector shapes.
    while (getline(file, line))
    {
        // Each line should start with a color code. After it, there should
        // be either one or two double values.
        // - If there is a single double value, create a Circle object.
        // - If there are two double values, create a Rectangle object.
        // - In both cases, push the newly created object to the vector shapes.

        vector<string> splitted_line = split(line, ' ', true);
        if (splitted_line.size() == 2)
        {
            char color = splitted_line[0][0];
            double radius = stod(splitted_line[1]);
            shapes.push_back(make_shared<Circle>(color, radius));
        }
        else if (splitted_line.size() == 3)
        {
            char color = splitted_line[0][0];
            double width = stod(splitted_line[1]);
            double height = stod(splitted_line[2]);
            shapes.push_back(make_shared<Rectangle>(color, width, height));
        }
    }
    print_shapes(shapes);
    return 0;
}
