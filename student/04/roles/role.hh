#ifndef ROLE_HH
#define ROLE_HH
#include <iostream>


class Role
{
public:
    // Constructor
    Role(int from_year);

    // Destructor
    virtual ~Role();

    // Prints the role in the format:
    // Role started at <from_year_>
    virtual void print(std::ostream& output) const;

private:
    int from_year_;
};

#endif // ROLE_HH
