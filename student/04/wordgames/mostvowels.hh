#ifndef MOSTVOWELS_HH
#define MOSTVOWELS_HH

#include "basegame.hh"

class MostVowels : public BaseGame
{
public:
    MostVowels(unsigned int rounds);
    virtual ~MostVowels();

    void printGameName() const override;
    unsigned int roundWinner(const std::string& word1,
                             const std::string& word2) const override;
};

#endif // MOSTVOWELS_HH