#include "mammal.hh"

// Constructor
// Calls Animal constructor and sets moving sound
Mammal::Mammal() :
    Animal("Kip kop kip kop")
{
}

// New method
void Mammal::suckle(std::ostream& output) const
{
    output << "Mus mus" << std::endl;
}