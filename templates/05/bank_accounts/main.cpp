#include "account.hh"
#include "creditaccount.hh"
#include "timedepositaccount.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Prints accounts stored in the given vector.
void print_accounts(const vector<Account*>& accs)
{
    cout << "Printing all accounts:" << endl;
    for(auto acc : accs)
    {
        cout << "  ";
        acc->print();
    }
    cout << endl;
}

// Prints credits of the accounts stored in the given vector.
// If an account is not a credit account, prints 0 as the credit.
// Each account is printed in the form:
// Account <iban> has credit: <credit>
void print_credits(const vector<Account*>& accs)
{
    cout << "Printing credits:" << endl;
    for(auto acc : accs)
    {
        cout << "  Account ";
        acc->print_iban();
        cout << " has credit: ";
        CreditAccount* credit_ptr = dynamic_cast<CreditAccount*>(acc);
        if(credit_ptr)
        {
            cout << credit_ptr->get_credit_limit() << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    cout << endl;
}

// Prints deposits of the accounts stored in the given vector.
// If an account is not a time deposit account, prints 0 as the deposit.
// Each account is printed in the form:
// Account <iban> has time deposit: <deposit>
void print_deposits(const vector<Account*>& accs)
{
    cout << "Printing deposits:" << endl;

    // TODO: Write the implementation here
}

int main()
{
    cout << "1: Creating three accounts and putting money to them" << endl << endl;
    Account normal_account("Jasper");
    CreditAccount credit_account("Jesper");
    TimeDepositAccount time_deposit_account("Joonatan");

    // Collecting accounts into a vector to be able to print them
    // by just going through the vector.
    // Actually pointers (the memory addresses of the accounts) are stored in
    // the vector to enable changes to be targeted also at the vector elements.
    vector<Account*> accounts;
    accounts.push_back(&normal_account);
    accounts.push_back(&credit_account);
    accounts.push_back(&time_deposit_account);

    // Setting credit limit for a credit account
    credit_account.set_credit_limit(100);

    // Setting time deposit for a time deposit account
    time_deposit_account.set_times(2); // 2 years

    // Putting money to each three accounts
    normal_account.save_money(100);
    credit_account.save_money(200);
    time_deposit_account.save_money(300);

    print_accounts(accounts);

    cout << "2: Taking and transforming money from a normal account:" << endl << endl;
    normal_account.take_money(50); // succeeds
    print_accounts(accounts);
    normal_account.take_money(70); // fails
    normal_account.transfer_to(&credit_account, 70); // fails
    normal_account.transfer_to(&credit_account, 10); // succeeds
    print_accounts(accounts);

    cout << "3: Taking and transforming money from a credit account:" << endl << endl;
    credit_account.take_money(100); // succeeds without credit
    print_accounts(accounts);
    credit_account.take_money(300); // fails
    credit_account.take_money(150); // succeeds with credit
    print_accounts(accounts);
    credit_account.transfer_to(&time_deposit_account, 100); // fails
    credit_account.transfer_to(&time_deposit_account, 10); // succeeds with credit
    print_accounts(accounts);

    cout << "4: Taking and transforming money from a time deposit account:" << endl << endl;
    time_deposit_account.take_money(10); // fails due to time
    time_deposit_account.transfer_to(&normal_account, 20); // fails due to time
    time_deposit_account.spend_time(800); // 800 days
    time_deposit_account.take_money(30); // succeeds
    print_accounts(accounts);
    time_deposit_account.take_money(400); // fails due to balance underflow
    time_deposit_account.transfer_to(&normal_account, 400); // fails due balance underflow
    time_deposit_account.transfer_to(&normal_account, 40); // succeeds
    print_accounts(accounts);

    cout << "5: Transforming money from an account to itself:" << endl << endl;;
    normal_account.transfer_to(&normal_account, 1000);
    credit_account.transfer_to(&credit_account, 1000);
    time_deposit_account.transfer_to(&time_deposit_account, 1000);
    print_accounts(accounts);

    cout << "6: Printing credit limits and time deposits:" << endl << endl;
    print_credits(accounts);
    print_deposits(accounts);

    return 0;
}
