#include "teacher.hh"
#include <iostream>
#include <algorithm>

// Constructor
Teacher::Teacher(const std::string& name, int age, const std::string office_num):
    Person(name, age),
    room_(office_num)
{
    std::cout << "Teacher created: " << get_name() << std::endl;
}

// Destructor
Teacher::~Teacher()
{
    std::cout << "Teacher destructed: " << get_name() << std::endl;
}

// Change room
void Teacher::change_room(const std::string& new_room)
{
    room_ = new_room;
}

// Add course
void Teacher::add_new_course(const std::string& course)
{
    courses_.push_back(course);
}

// Remove course
void Teacher::remove_course(const std::string& course)
{
    courses_.erase(std::remove(courses_.begin(), courses_.end(), course),
                   courses_.end());
}

// Print teacher data
void Teacher::print(std::ostream& output) const
{
    // Print name and age
    Person::print(output);

    output << "*** " << room_ << ": ";

    if(courses_.empty())
    {
        output << "No responsibilities";
    }
    else
    {
        // Copy and sort courses
        std::vector<std::string> sorted = courses_;
        std::sort(sorted.begin(), sorted.end());

        for(size_t i = 0; i < sorted.size(); ++i)
        {
            output << sorted.at(i);
            if(i != sorted.size() - 1)
            {
                output << ", ";
            }
        }
    }

    output << std::endl;
}

// Role
std::string Teacher::get_role() const
{
    return "teacher";
}