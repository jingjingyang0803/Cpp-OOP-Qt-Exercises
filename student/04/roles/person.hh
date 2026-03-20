#ifndef PERSON_HH
#define PERSON_HH

#include "role.hh"
#include <string>
#include <vector>

class Person
{
public:
    // Constructor
    Person(const std::string& name);

    // Destructor
    virtual ~Person();

    // Adds a new role for the person
    void add_role(Role* role);

    // Prints the roles
    void print(std::ostream& output) const;

    // Prints the name
    void print_name(std::ostream& output) const;

private:
    std::string name_;
    std::vector<Role*> roles_;
};

#endif // PERSON_HH
