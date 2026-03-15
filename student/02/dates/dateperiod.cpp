#include "dateperiod.hh"

// Constructor that takes two Date objects as parameters. The constructor should initialize the start and end members with the given dates, and also calculate the difference in days between the two dates and store it in the diff member. The difference should be a positive number, regardless of the order of the given dates.
DatePeriod::DatePeriod(const Date& d1, const Date& d2):
    start_(d1),
    end_(d2),
    diff_(0)
{
    unsigned int days1 = countDaysFromOrigin(start_);
    unsigned int days2 = countDaysFromOrigin(end_);

    if(days2 >= days1) {
        diff_ = days2 - days1;
    } else {
        diff_ = days1 - days2;
    }
}

DatePeriod::~DatePeriod()
{
}

std::string DatePeriod::getStart() const
{
    return start_.toIsoFormat();
}

std::string DatePeriod::getEnd() const
{
    return end_.toIsoFormat();
}

unsigned int DatePeriod::getDiff() const
{
    return diff_;
}

// Helper method that counts the number of days from a fixed origin date (e.g., 01.01.1000) to the given date. This method is used to calculate the difference in days between two dates.
unsigned int DatePeriod::countDaysFromOrigin(const Date& date) const
{
    unsigned int total = 0;

    for(int year = FIRST_YEAR; year < date.getYear(); ++year) {
        Date temp(year, 1, 1);
        total += temp.isLeapYear() ? 366 : 365;
    }

    for(int month = 1; month < date.getMonth(); ++month) {
        total += MONTH_SIZES[month - 1];
        if(month == 2) {
            Date temp(date.getYear(), 2, 1);
            if(temp.isLeapYear()) {
                total += 1;
            }
        }
    }

    total += date.getDay() - 1;
    return total;
}