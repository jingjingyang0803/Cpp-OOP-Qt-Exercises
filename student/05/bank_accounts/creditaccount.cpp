#include "creditaccount.hh"
#include <iostream>

CreditAccount::CreditAccount(const std::string& owner) : Account(owner)
{
}
CreditAccount::~CreditAccount()
{
}

bool CreditAccount::take_money(double amount)
{
    // Try using balance first
    if(Account::take_money(amount))
    {
        return true;
    }

    // Check credit limit
    if(get_credit_limit() - credit_used_ < amount)
    {
        std::cout << "Not enough money in the account, or credit limit would be gone over"
                  << std::endl;
        return false;
    }

    // Use credit
    credit_used_ += amount;
    return true;
}

void CreditAccount::print() const
{
    Account::print();
    std::cout << "Credit limit: " << credit_limit_ << std::endl;
}

void CreditAccount::set_credit_limit(double limit)
{
    credit_limit_ = limit;
}

double CreditAccount::get_credit_limit() const
{
    return credit_limit_;
}
