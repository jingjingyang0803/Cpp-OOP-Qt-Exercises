#ifndef PLAYER_HH
#define PLAYER_HH

#include "role.hh"
#include <string>

// Represents a player with one instrument.
class Player : public Role
{
public:
    // Constructor
    Player(int from_year);

    // Destructor
    virtual ~Player();

    // Updates the instrument to be played
    void add_instrument(const std::string& instrument);

    // Prints player's information
    void print(std::ostream& output) const;

private:
    std::string instrument_;
};

#endif // PLAYER_HH