#ifndef PROGRAMMER_HH
#define PROGRAMMER_HH

#include "role.hh"
#include <vector>
#include <string>

// Represents a programmer with multiple skills.
class Programmer : public Role
{
public:
    // Constructor
    Programmer(int from_year);

    // Destructor
    ~Programmer();

    // Adds a new skill
    void add_skill(const std::string& skill);

    // Prints programmer's information
    void print(std::ostream& output) const;

private:
    std::vector<std::string> skills_;
};

#endif // PROGRAMMER_HH