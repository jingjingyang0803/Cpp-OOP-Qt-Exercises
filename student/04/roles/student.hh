#ifndef STUDENT_HH
#define STUDENT_HH

#include "role.hh"

// Represents a student with a student number.
class Student : public Role
{
public:
    // Constructor
    Student(int from_year, int student_number);

    // Destructor
    ~Student();

    // Prints student's information
    void print(std::ostream& output) const;

private:
    int student_number_;
};

#endif // STUDENT_HH