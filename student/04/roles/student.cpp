#include "student.hh"

// Constructor
Student::Student(int from_year, int student_number):
    Role(from_year),
    student_number_(student_number)
{
}

// Destructor
Student::~Student()
{
}

void Student::print(std::ostream& output) const
{
    output << "Student number: " << student_number_ << std::endl;
}