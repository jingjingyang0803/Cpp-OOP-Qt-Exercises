#ifndef DATE_HH
#define DATE_HH

#include <string>

// Some bound values
const int FIRST_DAY = 1;
const int FIRST_MONTH = 1;
const int FIRST_YEAR = 1000;
const int LAST_YEAR = 9999;

// Number of days in months
int const MONTH_SIZES[12] = { 31, 28, 31, 30, 31, 30,
                              31, 31, 30, 31, 30, 31 };

class Date
{
public:
    // Constructor taking three ints as parameters.
    Date(int year, int month, int day);

    // Destructor
    virtual ~Date();

    // Obvious getter methods
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // Returns the date in the format dd.mm.yyyy
    std::string toString() const;

    // Returns the date in the format yyyy-mm-dd
    std::string toIsoFormat() const;

    // Comparison methods
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    // Returns true iff the year of the date is a leap year
    bool isLeapYear() const;

    // Checks the legality of the date.
    // The year must be in the interval [FIRST_YEAR..LAST_YEAR], the month must
    // be in the interval [1..12], the day must be greater or equal to 1 and
    // less or equal to the elements in the MONTH_SIZES array, and also leap
    // years are taken into account.
    bool isLegal() const;

private:
    int year_;
    int month_;
    int day_;
};

#endif // DATE_HH
