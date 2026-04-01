/*
Class DateException that inherits the C++ exception class domain_error.
*/

#ifndef DATEEXCEPTION_HH
#define DATEEXCEPTION_HH

#include <stdexcept>

class DateException : public std::domain_error {
public:
  /*
   * Constructor of form DateException(const char* message) that calls the
   * constructor of the superclass with the same parameter.
   * throws an exception of type DateException with a message of form “Illegal
   * time hour:minute:second”. Virtual destructor.
   */
  DateException(const char *message) : std::domain_error(message) {}

  /**
   * Virtual destructor.
   */
  virtual ~DateException() noexcept {}
};

#endif // DATEEXCEPTION_HH
