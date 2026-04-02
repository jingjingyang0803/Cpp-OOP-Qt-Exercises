#include "timedepositaccount.hh"
#include <iostream>

TimeDepositAccount::TimeDepositAccount(const std::string& owner) : Account(owner)
{
}

TimeDepositAccount::~TimeDepositAccount()
{
}

bool TimeDepositAccount::take_money(double amount)
{
    if(days_left_ <= 0)
    {
        return Account::take_money(amount);
    }
    std::cout << "Cannot take money, deposit time left: " << days_left_ << " days" << std::endl;
    return false;
}

void TimeDepositAccount::print() const
{
    Account::print();
    std::cout << "Days left: " << days_left_ << std::endl;
}

void TimeDepositAccount::set_times(int years)
{
    days_left_ = years * 365;
}

int TimeDepositAccount::get_times() const
{
    return days_left_ / 365;
}

void TimeDepositAccount::spend_time(int days)
{
    if(days > days_left_)
    {
        std::cout << "Cannot spend time, not enough time left" << std::endl;
        return;
    }
    days_left_ -= days;
}
