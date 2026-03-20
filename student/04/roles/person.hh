#ifndef PERSON_HH
#define PERSON_HH

#include "role.hh"
#include <string>
#include <vector>
#include <iostream>

// Represents a person with multiple roles.
class Person
{
public:
    // Constructor
    Person(const std::string& name);

    // Destructor
    ~Person();

    // Prints person's name
    void print_name(std::ostream& output) const;

    // Adds a new role
    void add_role(Role* role);

    // Prints person's all roles starting year
    void print(std::ostream& output) const;

private:
    std::string name_;
    std::vector<Role*> roles_;
};

#endif // PERSON_HH