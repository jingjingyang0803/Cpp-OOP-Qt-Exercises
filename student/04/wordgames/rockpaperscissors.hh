#ifndef ROCKPAPERSCISSORS_HH
#define ROCKPAPERSCISSORS_HH

#include "basegame.hh"

// Implements the Rock-Paper-Scissors game.
class RockPaperScissors : public BaseGame
{
public:
    // Constructor
    RockPaperScissors(unsigned int rounds);

    // Destructor
    ~RockPaperScissors();

    // Print the name of the game.
    void printGameName() const;

    // Determine the winner of a round.
    // Valid words: "rock", "paper", "scissors" (case-insensitive).
    // - If both words are valid:
    //     rock beats scissors, scissors beats paper, paper beats rock
    //     same words -> tie
    // - If both words are invalid -> tie
    // - If only one word is valid -> the valid one wins
    // Return 1 if player1 wins, 2 if player2 wins, 0 if tie.
    unsigned int roundWinner(const std::string& word1,
                             const std::string& word2) const;
};

#endif // ROCKPAPERSCISSORS_HH