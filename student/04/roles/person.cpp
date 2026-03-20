#include "person.hh"

// Constructor
Person::Person(const std::string& name):
    name_(name)
{
}

// Destructor
Person::~Person()
{
    for(Role* role : roles_)
    {
        delete role;
    }
}

// Print only name
void Person::print_name(std::ostream& output) const
{
    output << name_ << std::endl;
}

// Add role
void Person::add_role(Role* role)
{
    roles_.push_back(role);
}

// Print name + all roles
void Person::print(std::ostream& output) const
{

    for(Role* role : roles_)
    {
        role->print(output);
    }
}