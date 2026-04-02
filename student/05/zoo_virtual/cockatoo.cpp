#include "cockatoo.hh"

Cockatoo::Cockatoo() {}

Cockatoo::~Cockatoo() {}

void Cockatoo::vocalize(std::ostream &output) const {
  output << "Kee-ow kee-ow!" << std::endl;
}