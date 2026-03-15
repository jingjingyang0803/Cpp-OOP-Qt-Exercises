#include "date.hh"
#include <sstream>
#include <iomanip>

Date::Date(int year, int month, int day):
    year_(year),
    month_(month),
    day_(day)
{
}

Date::~Date()
{
}

int Date::getYear() const
{
    return year_;
}

int Date::getMonth() const
{
    return month_;
}

int Date::getDay() const
{
    return day_;
}
// Formats the date as dd.mm.yyyy, with leading zeros for day and month, and four digits for the year.
std::string Date::toString() const
{
    std::ostringstream out;
    out << std::setw(2) << std::setfill('0') << day_ << "."
        << std::setw(2) << std::setfill('0') << month_ << "."
        << std::setw(4) << std::setfill('0') << year_;
    return out.str();
}

// Formats the date as yyyy-mm-dd, with leading zeros for day and month, and four digits for the year.
std::string Date::toIsoFormat() const
{
    std::ostringstream out;
    out << std::setw(4) << std::setfill('0') << year_ << "-"
        << std::setw(2) << std::setfill('0') << month_ << "-"
        << std::setw(2) << std::setfill('0') << day_;
    return out.str();
}

// Compares two dates. A date is less than another date if it is earlier than the other date.
bool Date::operator<(const Date& other) const
{
    if(year_ != other.year_) {
        return year_ < other.year_;
    }
    if(month_ != other.month_) {
        return month_ < other.month_;
    }
    return day_ < other.day_;
}

// Two dates are equal if they have the same year, month, and day.
bool Date::operator==(const Date& other) const
{
    return year_ == other.year_
        && month_ == other.month_
        && day_ == other.day_;
}

// A year is a leap year if it is divisible by 4, but not divisible by 100, unless it is also divisible by 400.
bool Date::isLeapYear() const
{
    return (year_ % 4 == 0) and ((year_ % 100 != 0) or (year_ % 400 == 0));
}

bool Date::isLegal() const
{
    if(year_ < FIRST_YEAR || year_ > LAST_YEAR) {
        return false;
    }

    if(month_ < 1 || month_ > 12) {
        return false;
    }

    if(day_ < 1) {
        return false;
    }

    int max_days = MONTH_SIZES[month_ - 1];
    if(month_ == 2 && isLeapYear()) {
        max_days = 29;
    }

    return day_ <= max_days;
}
