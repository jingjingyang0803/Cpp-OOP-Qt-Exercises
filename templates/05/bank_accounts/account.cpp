#include "account.hh"
#include <iostream>

// Initialize the static attribute running_number_
int Account::running_number_ = 0;

Account::Account(const std::string& owner)
{
    generate_iban();
}

Account::~Account()
{

}

TODO: Implement more functions here

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
