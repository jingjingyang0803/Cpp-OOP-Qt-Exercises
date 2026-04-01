/*
Class DateTime that inherits the class Date and in addition stores information
about time, that is, hour, minute and second.
*/

#ifndef DATETIME_HH
#define DATETIME_HH

#include "date.hh"
#include <iomanip>
#include <sstream>
#include <string>

class DateTime : public Date {
public:
  // Constructor that initializes the object according to the parameters. The
  // constructor checks if the time is legal (hour 0–23, minute and second
  // 0–59), and if it is not, throws an exception of type DateException with a
  // message of form “Illegal time hour:minute:second”. Each part of the time is
  // expressed using two digits.
  DateTime(int year, int month, int day, int hour, int minute, int second);
  virtual ~DateTime();

  int getHour() const;
  int getMinute() const;
  int getSecond() const;

  // Member function string toString() that returns a string formed by first the
  // string returned by toString of the superclass Date, then a space, and then
  // a string that represents this object’s time in the form
  // “hour:minute:second”. Each part of the time is expressed using two digits.
  //   The function may call toString of the superclass. First perform this call
  //   and then append the result with a space and a time string of the form
  //   described above.
  std::string toString() const;

private:
  int hour_;
  int minute_;
  int second_;
};

#endif // DATETIME_HH