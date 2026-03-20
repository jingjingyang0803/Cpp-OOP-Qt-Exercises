#include "player.hh"

// Constructor
Player::Player(int from_year):
    Role(from_year),
    instrument_("")
{
}

// Destructor
Player::~Player()
{
}

void Player::add_instrument(const std::string& instrument)
{
    instrument_ = instrument;
}

void Player::print(std::ostream& output) const
{
    if(instrument_.empty())
    {
        output << "No instrument" << std::endl;
    }
    else
    {
        output << "Instrument to be played: " << instrument_ << std::endl;
    }
}