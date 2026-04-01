#include "datetime.hh"
#include "dateexception.hh"
#include <iomanip>

DateTime::DateTime(int year, int month, int day, int hour, int minute,
                   int second)
    : Date(year, month, day), hour_(hour), minute_(minute), second_(second) {
  if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 ||
      second > 59) {
    std::ostringstream oss;
    oss << "Illegal time " << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":" << std::setw(2)
        << std::setfill('0') << second;
    throw DateException(oss.str().c_str());
  }
}

DateTime::~DateTime() {}

int DateTime::getHour() const { return hour_; }

int DateTime::getMinute() const { return minute_; }

int DateTime::getSecond() const { return second_; }

std::string DateTime::toString() const {
  std::ostringstream out;
  out << Date::toString() << " " << std::setw(2) << std::setfill('0') << hour_
      << ":" << std::setw(2) << std::setfill('0') << minute_ << ":"
      << std::setw(2) << std::setfill('0') << second_;
  return out.str();
}
