#ifndef MOSTVOWELS_HH
#define MOSTVOWELS_HH

#include "basegame.hh"

// Implements a game where the word with the most vowels wins.
class MostVowels : public BaseGame
{
public:
    // Constructor
    MostVowels(unsigned int rounds);

    // Destructor
    ~MostVowels();

    // Print the name of the game.
    void printGameName() const;

    // Determine the winner of a round.
    // Vowels considered: a, e, i, o, u , y(case-insensitive).
    // The word containing more vowels wins.
    // If both words have the same number of vowels -> tie.
    // Return 1 if player1 wins, 2 if player2 wins, 0 if tie.
    unsigned int roundWinner(const std::string& word1,
                             const std::string& word2) const;
};

#endif // MOSTVOWELS_HH