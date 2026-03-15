#include "date.hh"

TODO: Implement other functions here

bool Date::isLeapYear() const
{
    return (year_ % 4 == 0) and ((year_ % 100 != 0) or (year_ % 400 == 0));
}

