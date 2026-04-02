#ifndef ELEPHANT_HH
#define ELEPHANT_HH

#include "mammal.hh"

class Elephant : public Mammal {
public:
  // Constructor
  Elephant();

  // Destructor
  virtual ~Elephant() = default;

  // New functionality
  void vocalize(std::ostream &output) const;
};

#endif // ELEPHANT_HH