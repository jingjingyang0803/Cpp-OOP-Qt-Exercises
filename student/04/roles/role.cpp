#include "role.hh"

Role::Role(int from_year):
    from_year_(from_year)
{
}

Role::~Role()
{
}

void Role::print(std::ostream& output) const
{
    output << "Role started at " << from_year_ << std::endl;
}