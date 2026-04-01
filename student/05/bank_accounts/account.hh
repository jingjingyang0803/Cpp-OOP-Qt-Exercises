#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner);

    // Virtual destructor
    virtual ~Account();

    // Saves money for the account as much as given in the parameter amount.
    virtual void save_money(double amount);

    // Takes money from the account as much as given in the parameter amount,
    // if possible.
    // Taking money fails if there is not enough money in the account.
    // Returns false, if taking money fails, otherwise returns true.
    virtual bool take_money(double amount);

    // Transfers money from the account to another account given in the
    // parameter other_account, as much as given in the parameter amount,
    // if possible.
    // In other words, takes money from the account and saves money
    // for the account other_account.
    // Transferring may fail for the same reasons as taking money.
    // On the hand, transferring succeeds with any amount of money,
    // if transferring happens from an account to itself, since
    // this actually makes nothing´.
    // Returns false, if transferring money fails, otherwise returns true.
    virtual bool transfer_to(Account* other_account, double amount);

    // Prints all data about the account (owner : IBAN : balance).
    virtual void print() const;

    // Prints the iban of the account.
    void print_iban() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;
};

#endif // ACCOUNT_HH
