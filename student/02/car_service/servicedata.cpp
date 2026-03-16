#include "servicedata.hh"
#include <iostream>

// Constructor
ServiceData::ServiceData() = default;

// Destructor
ServiceData::~ServiceData() = default;


// Inserts service information to the map.
// Key is kilometres driven.
// If the same kilometres already exists, prints error.
bool ServiceData::makeService(const Service& service, int kilometres)
{
    // Check if service already exists at this kilometre value
    if (services_.find(kilometres) != services_.end()) {
        std::cout << "Error: already serviced with the same kilometres" << std::endl;
        return false;
    }

    // Insert new service
    services_[kilometres] = service;
    return true;
}


// Prints all services stored in the map
void ServiceData::print() const
{
    for (const auto& pair : services_) {
        int kilometres = pair.first;
        const Service& service = pair.second;

        std::cout << "* Kilometres driven " << kilometres
                  << " until " << service.date_ << std::endl;

        // Print operations
        for (const auto& op : service.operations_) {
            std::cout << "  --- " << op << std::endl;
        }
    }
}


// Getter for the service map
const std::map<int, Service>& ServiceData::getServices() const
{
    return services_;
}