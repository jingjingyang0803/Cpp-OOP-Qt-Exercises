/*
Class TimeDepositAccount that inherits the class Account and stores the time deposit in years and
the number of days telling how much there deposit time left.
*/

#ifndef TIMEDEPOSITACCOUNT_HH
#define TIMEDEPOSITACCOUNT_HH

#include "account.hh"
#include <string>

class TimeDepositAccount : public Account
{
public:
    TimeDepositAccount(const std::string& owner);
    virtual ~TimeDepositAccount();

    // Takes money from the account as much as given in the parameter amount
    // if possible.
    // Taking money fails if there is not enough money in the account, or if there deposit time
    // left. Returns false, if taking money fails, otherwise returns true.
    virtual bool take_money(double amount) override;

    // Prints all data about the account, including time deposit left.
    // in the form :: : Days left : <days left>.
    void virtual print() const override;
    void set_times(int years);
    int get_times() const;

    // Spends time, i.e. decreases the days left by the given amount of days.
    // Leap years are not taken into account, so each year has 365 days.
    void spend_time(int days);

private:
    int days_left_;
};

#endif // TIMEDEPOSITACCOUNT_HH
