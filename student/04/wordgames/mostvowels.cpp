#include "mostvowels.hh"
#include <iostream>
#include <cctype>

MostVowels::MostVowels(unsigned int rounds):
    BaseGame(rounds)
{
}

MostVowels::~MostVowels()
{
}

void MostVowels::printGameName() const
{
    std::cout << "Most Vowels Game" << std::endl;
}

unsigned int MostVowels::roundWinner(const std::string& word1,
                                     const std::string& word2) const
{
    auto count_vowels = [](const std::string& word) {
        unsigned int count = 0;
        for(char ch : word)
        {
            ch = std::tolower(static_cast<unsigned char>(ch));
            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y')
            {
                ++count;
            }
        }
        return count;
    };

    unsigned int vowels1 = count_vowels(word1);
    unsigned int vowels2 = count_vowels(word2);

    if(vowels1 > vowels2)
    {
        return 1;
    }
    else if(vowels2 > vowels1)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}