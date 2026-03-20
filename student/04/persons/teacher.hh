#ifndef TEACHER_HH
#define TEACHER_HH

#include "person.hh"
#include <vector>
#include <string>

// Represents a teacher with a room and course responsibilities.
class Teacher : public Person
{
public:
    // Constructor
    Teacher(const std::string& name, int age, const std::string office_num);

    // Destructor
    ~Teacher();

    // Changes the room number
    void change_room(const std::string& new_room);

    // Adds a new course responsibility
    void add_new_course(const std::string& course);

    // Removes a course responsibility
    void remove_course(const std::string& course);

    // Prints teacher's information
    void print(std::ostream& output) const;

protected:
    // Returns the role of the person
    std::string get_role() const;

private:
    std::string room_;
    std::vector<std::string> courses_;
};

#endif // TEACHER_HH