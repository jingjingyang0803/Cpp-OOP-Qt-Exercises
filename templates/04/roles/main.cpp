#include "person.hh"
#include "player.hh"
#include "programmer.hh"
#include "student.hh"
#include <iostream>

using namespace std;

int main()
{
    cout << "*** One person: ";
    Person person1("Matti");
    person1.print_name(cout);
    Player player1(2024);
    player1.add_instrument("violin");
    person1.add_role(&player1);
    player1.print(cout);
    Student student1(2023, 123456);
    person1.add_role(&student1);
    student1.print(cout);
    person1.print(cout);

    cout << endl << "*** Another person: ";
    Person person2("Teppo");
    person2.print_name(cout);
    Player player2(2000);
    player2.add_instrument("guitar");
    person2.add_role(&player2);
    player2.print(cout);
    Programmer programmer2(2001);
    programmer2.add_skill("Python");
    programmer2.add_skill("C++");
    person2.add_role(&programmer2);
    programmer2.print(cout);
    person2.print(cout);
    return 0;
}
