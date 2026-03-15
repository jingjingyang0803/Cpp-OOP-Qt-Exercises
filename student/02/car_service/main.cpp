#include "car.hh"
#include <iostream>

using namespace std;

int main()
{
    Car car1("Toyota", "Avensis", "grey", "GEC-156");
    car1.drive(100);
    car1.service("2024-12-13", {"motor oil change", "brake fix"});

    Car car2(car1); // Calls copy constructor
    car2.setRegisterNum("IV-10");
    car2.drive(1000);
    car2.service("2025-01-01", {"brake fix", "timing belt change"});
    // Not driven between services
    car2.service("2025-01-02", {"motor oil change"});

    car1.drive(500);
    car1.service("2026-01-01", {"exhaust system change", "timing belt change"});

    car1.print();
    car2.print();
    car1 = car2; // Assumes assignment operator defined
    car1.print();
    car2.print();

    cout << "End of main" << endl;
    return 0;
}
