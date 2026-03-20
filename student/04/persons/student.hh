#ifndef STUDENT_HH
#define STUDENT_HH

#include "person.hh"
#include <vector>
#include <string>

// Represents a student with an id and completed courses.
class Student : public Person
{
public:
    // Constructor
    Student(const std::string& name, int age, const std::string student_num);

    // Destructor
    ~Student();

    // Registers a completed course
    void complete_course(const std::string& course);

    // Prints student's information
    void print(std::ostream& output) const;

protected:
    // Returns the role of the person
    std::string get_role() const;

private:
    std::string student_num_;
    std::vector<std::string> courses_;
};

#endif // STUDENT_HH