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

void Account::save_money(double amount)
{
    balance_ += amount;
    std::cout << "Saving money: " << amount << std::endl;
}

bool Account::take_money(double amount)
{
    if(balance_ < amount)
    {
        std::cout << "Not enough money in the account" << std::endl;
        return false;
    }
    balance_ -= amount;

    std::cout << "Taking money: " << amount << std::endl;
    return true;
}

bool Account::transfer_to(Account* other_account, double amount)
{
    if(this == other_account)
    {
        std::cout << "Transferring money to the same account: " << amount << std::endl;
        return true;
    }
    if(take_money(amount))
    {
        other_account->save_money(amount);
        std::cout << "Transferring money: " << amount << std::endl;
        return true;
    }
    return false;
}

void Account::print() const
{
    std::cout << "owner: " << owner_ << " : IBAN: " << iban_ << " : balance: " << balance_
              << std::endl;
}

void Account::print_iban() const
{
    std::cout << "IBAN: " << iban_ << std::endl;
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
