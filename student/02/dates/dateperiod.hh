#ifndef DATEPERIOD_HH
#define DATEPERIOD_HH

#include "date.hh"
#include <string>

class DatePeriod
{
public:
    DatePeriod(const Date& d1, const Date& d2);
    virtual ~DatePeriod();

    std::string getStart() const;
    std::string getEnd() const;
    unsigned int getDiff() const;

private:
    Date start_;
    Date end_;
    unsigned int diff_;

    unsigned int countDaysFromOrigin(const Date& date) const;
};

#endif // DATEPERIOD_HH