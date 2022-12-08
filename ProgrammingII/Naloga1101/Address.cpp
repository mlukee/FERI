#include "Address.h"
#include <sstream>

Address::Address(std::string street, std::string post, std::string country) : street(street), post(post), country(country) {}

std::string Address::toString() const {
    std::stringstream ss;
    ss << street << ", " << post << ", " << country;
    return ss.str();
}
