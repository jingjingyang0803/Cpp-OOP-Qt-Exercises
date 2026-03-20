#include "person.hh"
#include "student.hh"
#include "teacher.hh"
#include <iostream>

using namespace std;

int main()
{
    // Creating and testing person
    Person person("somebody", 30);
    person.print(cout);
    person.celebrate_birthday(31);
    person.print(cout);
    cout << endl;

    // Creating and testing student
    Student student("student", 20, "xyz123");
    student.print(cout);
    student.celebrate_birthday(21);
    student.complete_course("Programming 1");
    student.print(cout);
    student.complete_course("Programming 2");
    student.complete_course("Data Structures and Algorithms");
    student.print(cout);
    cout << endl;

    // Creating and testing teacher
    Teacher teacher("teacher", 40, "TF113");
    teacher.print(cout);
    teacher.celebrate_birthday(41);
    teacher.add_new_course("Programming 3");
    teacher.print(cout);
    teacher.add_new_course("Programming 2");
    teacher.add_new_course("Programming 1");
    teacher.print(cout);
    teacher.remove_course("Programming 2");
    teacher.print(cout);
    cout << endl;

    // Assigning a subclass object to the base class object
    person = student;
    person.print(cout);
    person = teacher;
    person.print(cout);
    cout << endl;

    return 0;
}
