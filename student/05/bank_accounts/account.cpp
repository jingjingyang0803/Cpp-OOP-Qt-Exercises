#include "account.hh"
#include <iostream>

// Initialize the static attribute running_number_
int Account::running_number_ = 0;

Account::Account(const std::string& owner)
{
    owner_ = owner;
    balance_ = 0.0;
    generate_iban();
}

Account::~Account()
{
}

void Account::save_money(double amount)
{
    balance_ += amount;
}

bool Account::take_money(double amount)
{
    if(balance_ < amount)
    {
        return false;
    }
    balance_ -= amount;

    return true;
}

bool Account::transfer_to(Account* other_account, double amount)
{
    if(this == other_account)
    {
        return true;
    }
    if(take_money(amount))
    {
        other_account->save_money(amount);
        return true;
    }
    return false;
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::print_iban() const
{
    std::cout << iban_;
}

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
