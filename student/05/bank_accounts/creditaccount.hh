#ifndef CREDITACCOUNT_HH
#define CREDITACCOUNT_HH

#include "account.hh"

class CreditAccount : public Account
{
public:
    // Constructor
    CreditAccount(const std::string& owner);

    // Virtual destructor
    virtual ~CreditAccount();

    // Takes money from the account as much as given in the parameter amount
    // if possible.
    // Taking money fails if there is not enough money in the account,
    // or if the possible credit limit would be gone over.
    // Returns false, if taking money fails, otherwise returns true.
    bool virtual take_money(double amount);

    // Prints all data about the account, including credit limit.
    void virtual print() const;

    // Sets the credit limit.
    void set_credit_limit(double limit);

    // Returns the credit limit.
    double get_credit_limit() const;

private:
    double credit_limit_;
};

#endif // CREDITACCOUNT_HH

