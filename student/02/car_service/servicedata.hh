#ifndef SERVICEDATA_HH
#define SERVICEDATA_HH

#include <string>
#include <vector>
#include <map>

struct Service
{
    std::string date_;
    std::vector<std::string> operations_;
};

class ServiceData
{
public:
    // Constructor
    ServiceData();

    // Destructor
    virtual ~ServiceData();

    // Inserts the given data in the services_map, if the car has been driven
    // after the previous service, but if a service can be found from the
    // services_ map with the same kilometres, prints the error message
    // "Error: already serviced with the same kilometres".
    bool makeService(const Service& service, int kilometres);

    // Prints all services made. Each service is printed in the format:
    // * Kilometres driven <kilometres> until <date>
    //   --- service 1
    //   --- service 2
    //   --- etc.
    void print() const;

    // Returns the service data as a map
    const std::map<int, Service>& getServices() const;

private:
    std::map<int /* kilometres */, Service> services_;
};

#endif // SERVICEDATA_HH
