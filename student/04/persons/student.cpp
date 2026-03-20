#include "student.hh"
#include <iostream>

// Constructor
Student::Student(const std::string& name, int age, const std::string student_num):
    Person(name, age),
    student_num_(student_num)
{
    std::cout << "Student created: " << get_name() << std::endl;
}

// Destructor
Student::~Student()
{
    std::cout << "Student destructed: " << get_name() << std::endl;
}

// Add a completed course
void Student::complete_course(const std::string& course)
{
    courses_.push_back(course);
}

// Print student data
void Student::print(std::ostream& output) const
{
    // print name and age (reuse base functionality)
    Person::print(output);

    output << "+++ " << student_num_ << ": ";

    if(courses_.empty())
    {
        output << "No courses completed";
    }
    else
    {
        for(size_t i = 0; i < courses_.size(); ++i)
        {
            output << courses_.at(i);
            if(i != courses_.size() - 1)
            {
                output << ", ";
            }
        }
    }

    output << std::endl;
}

// Role for polymorphism
std::string Student::get_role() const
{
    return "student";
}