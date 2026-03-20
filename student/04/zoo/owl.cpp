#include "owl.hh"

Owl::Owl()
{
}

Owl::~Owl()
{
}

void Owl::hoot(std::ostream &output) const
{
    output << "Hoo hoo!" << std::endl;
}
