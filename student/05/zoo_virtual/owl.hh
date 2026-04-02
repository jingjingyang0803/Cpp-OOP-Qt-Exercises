#ifndef OWL_HH
#define OWL_HH
#include"bird.hh"

class Owl: public Bird
{
public:
    Owl();
    virtual ~Owl();
    void hoot(std::ostream& output) const;
private:
    // attributes
};

#endif // OWL_HH
