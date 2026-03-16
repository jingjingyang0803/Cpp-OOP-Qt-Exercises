#include "car.hh"
#include <iostream>

// Default constructor
// Initializes strings empty, kilometresDriven_ to 0,
// and creates a unique ServiceData object.
Car::Car():
    brand_(""),
    model_(""),
    color_(""),
    registerNum_(""),
    kilometresDriven_(0),
    service_data_(std::make_unique<ServiceData>())
{
}

// Constructor with parameters
// Sets the given brand, model, color and register number.
// Kilometres is initialized to 0 and a new ServiceData object is created.
Car::Car(const std::string& brand, const std::string& model,
         const std::string& color, const std::string& regNum):
    brand_(brand),
    model_(model),
    color_(color),
    registerNum_(regNum),
    kilometresDriven_(0),
    service_data_(std::make_unique<ServiceData>())
{
}

// Copy constructor
// Copies brand, model and color from the other car.
// Register number is set empty and kilometres to 0.
// Creates a new independent ServiceData object.
Car::Car(const Car& other):
    brand_(other.brand_),
    model_(other.model_),
    color_(other.color_),
    registerNum_(""),
    kilometresDriven_(0),
    service_data_(std::make_unique<ServiceData>())
{
}

// Destructor
Car::~Car() = default;


// Assignment operator
// Copies brand, model and color.
// Register number is cleared, kilometres reset to 0,
// and a new ServiceData object is created.
Car& Car::operator=(const Car& other)
{
    if (this != &other) {
        brand_ = other.brand_;
        model_ = other.model_;
        color_ = other.color_;
        registerNum_.clear();
        kilometresDriven_ = 0;

        // Create a new service data (unique_ptr cannot be copied)
        service_data_ = std::make_unique<ServiceData>();
    }
    return *this;
}

// Setter for register number
void Car::setRegisterNum(const std::string& regNum)
{
    registerNum_ = regNum;
}

// Setter for color
void Car::setColor(const std::string& color)
{
    color_ = color;
}

// Getter functions
std::string Car::brand() const
{
    return brand_;
}

std::string Car::model() const
{
    return model_;
}

std::string Car::color() const
{
    return color_;
}

std::string Car::registerNum() const
{
    return registerNum_;
}

int Car::kilometresDriven() const
{
    return kilometresDriven_;
}

// Returns reference to service data
const ServiceData& Car::serviceData() const
{
    return *service_data_;
}

// Drive the car: increase kilometres driven
void Car::drive(int kilometres)
{
    kilometresDriven_ += kilometres;
}

// Insert service using an existing Service struct
bool Car::service(const Service& service)
{
    return service_data_->makeService(service, kilometresDriven_);
}

// Create a Service object and insert it
bool Car::service(const std::string& date,
                  const std::vector<std::string>& operations)
{
    Service service{date, operations};
    return service_data_->makeService(service, kilometresDriven_);
}

// Print car information and service data
void Car::print() const
{
    std::cout << registerNum_ << " : "
              << brand_ << " : "
              << model_ << " : "
              << color_ << std::endl;

    service_data_->print();
}