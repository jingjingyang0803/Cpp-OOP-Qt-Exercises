#ifndef MAMMAL_HH
#define MAMMAL_HH

#include "animal.hh"

class Mammal : public Animal
{
public:
    // Constructor
    Mammal();

    // Destructor (good practice with inheritance)
    virtual ~Mammal() = default;

    // New functionality
    void suckle(std::ostream& output) const;
};

#endif // MAMMAL_HH