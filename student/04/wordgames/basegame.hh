#ifndef BASEGAME_HH
#define BASEGAME_HH

#include <string>

struct Player
{
    std::string name;
    unsigned int wins;
};

class BaseGame
{
public:
    // Constructor
    BaseGame(unsigned int rounds);

    // Destructor
    virtual ~BaseGame();

    // Set names for the players.
    void setPlayers(const std::string& name1, const std::string& name2);

    // Play the game the given number of rounds (rounds_).
    // On each round, ask input from both players and tells the winner
    // of a round, or declare a tie.
    // After all rounds call reportWinner.
    void play();

private:
    // Ask input from the given player.
    std::string askInput(const Player& player) const;

    // Print the name of the game.
    virtual void printGameName() const;

    // Determine the winner of a round.
    // Return 1 if word1 is better, return 2 if word2 is better,
    // return 0 if word1 and word2 are equal.
    // Here (in the default case) longer word is better.
    virtual unsigned int roundWinner(const std::string& word1,
                                     const std::string& word2) const;

    // Print the total wins of both players.
    virtual void reportResult() const;

    // Rounds to be played
    unsigned int rounds_;

    // Players of the game
    Player player1_;
    Player player2_;
};

#endif // BASEGAME_HH
