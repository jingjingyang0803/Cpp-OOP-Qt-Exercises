#ifndef CAR_HH
#define CAR_HH

#include "servicedata.hh"
#include <string>
#include <memory>

class Car
{
public:
    // Default constructor.
    // Sets empty strings for the string attributes,
    // sets the kilometresDriven_ as 0, and makes a unique service data.
    Car();

    // Constructor.
    // Sets the given values for the corresponding attributes,
    // sets the kilometresDriven_ as 0, and makes a unique service data.
    Car(const std::string& brand, const std::string& model,
        const std::string& color, const std::string& regNum);

    // Copy constructor.
    // Sets the attributes as the values copied from the other car,
    // but sets the register number as an empty string and the
    // kilometresDriven_ as 0, and makes a unique service data.
    Car(const Car& other);

    // Destructor
    virtual ~Car();

    // Assignment operator
    Car& operator=(const Car& other);

    // Obvious setter functions
    void setRegisterNum(const std::string& regNum);
    void setColor(const std::string& color);

    // Getter functions for the attributes, return the corresponding attribute
    std::string brand() const;
    std::string model() const;
    std::string color() const;
    std::string registerNum() const;
    int kilometresDriven() const;
    const ServiceData& serviceData() const;

    // Drives the car, i.e. increases kilometres with the given number
    void drive(int kilometres);

    // Tries to insert the given service in the service data.
    // Returns the result of the service data's makeService function.
    bool service(const Service& service);

    // Creates a service with the given data and inserts the created service
    // in the service data. Returns the result of the service data's makeService function.
    bool service(const std::string& date,
                 const std::vector<std::string>& operations);

    // Prints the car data in the format:
    // <register number> : <brand> : <model> : <color>
    // and asks the service data to print itself.
    void print() const;

private:
    std::string brand_;
    std::string model_;
    std::string color_;
    std::string registerNum_;
    int kilometresDriven_;
    std::unique_ptr<ServiceData> service_data_;
};

#endif // CAR_HH
