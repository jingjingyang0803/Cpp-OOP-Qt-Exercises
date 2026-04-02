#include "elephant.hh"

// Constructor
// Mammal constructor already sets the correct moving sound
Elephant::Elephant() : Mammal() {}

// New method
void Elephant::vocalize(std::ostream &output) const {
  output << "Baraag baraag!" << std::endl;
}