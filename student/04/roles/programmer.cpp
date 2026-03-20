#include "programmer.hh"
#include <algorithm>

// Constructor
Programmer::Programmer(int from_year):
    Role(from_year)
{
}

// Destructor
Programmer::~Programmer()
{
}

void Programmer::add_skill(const std::string& skill)
{
    skills_.push_back(skill);
}

void Programmer::print(std::ostream& output) const
{
    if(skills_.empty())
    {
        output << "No skills" << std::endl;
    }
    else
    {
        std::vector<std::string> sorted = skills_;
        std::sort(sorted.begin(), sorted.end());

        output << "Skills: ";

        for(size_t i = 0; i < sorted.size(); ++i)
        {
            output << sorted.at(i);
            if(i != sorted.size() - 1)
            {
                output << " ";
            }
        }

        output << std::endl;
    }
}