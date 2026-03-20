#include "rockpaperscissors.hh"
#include <iostream>
#include <algorithm>

RockPaperScissors::RockPaperScissors(unsigned int rounds):
    BaseGame(rounds)
{
}

RockPaperScissors::~RockPaperScissors()
{
}

void RockPaperScissors::printGameName() const
{
    std::cout << "Rock-Paper-Scissors Game" << std::endl;
}

// helper: convert string to lowercase
static std::string to_lower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}

// helper: check valid word
static bool is_valid(const std::string& word)
{
    return word == "rock" || word == "paper" || word == "scissors";
}

unsigned int RockPaperScissors::roundWinner(const std::string& word1,
                                            const std::string& word2) const
{
    std::string w1 = to_lower(word1);
    std::string w2 = to_lower(word2);

    bool valid1 = is_valid(w1);
    bool valid2 = is_valid(w2);

    // both invalid -> tie
    if(!valid1 && !valid2)
    {
        return 0;
    }

    // one valid -> valid wins
    if(valid1 && !valid2)
    {
        return 1;
    }
    if(!valid1 && valid2)
    {
        return 2;
    }

    // both valid
    if(w1 == w2)
    {
        return 0;
    }

    // game rules
    if( (w1 == "rock" && w2 == "scissors") ||
        (w1 == "paper" && w2 == "rock") ||
        (w1 == "scissors" && w2 == "paper") )
    {
        return 1;
    }
    else
    {
        return 2;
    }
}