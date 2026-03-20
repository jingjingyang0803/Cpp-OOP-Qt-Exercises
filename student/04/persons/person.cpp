#include "person.hh"

// Constructor
Person::Person(const std::string& name, int age):
    name_(name), age_(age)
{
    std::cout << "created: " << get_role() << std::endl;
}

// Destructor
Person::~Person()
{
    std::cout << "destructed: " << get_role() << std::endl;
}

std::string Person::get_name() const
{
    return name_;
}

void Person::celebrate_birthday(int next_age)
{
    age_ = next_age;
}

void Person::print(std::ostream& output) const
{
    output << name_ << " : " << age_ << std::endl;
}

// Default role
std::string Person::get_role() const
{
    return "Person";
}