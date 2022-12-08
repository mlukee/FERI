#include "UnderFloorHeating.h"
#include <sstream>

UnderFloorHeating::UnderFloorHeating(std::string id, std::string name, float houseTmp) : Device(id, name), houseTmp(houseTmp){}

std::string UnderFloorHeating::toString() const {
    std::stringstream ss;
    ss << Device::toString() << "\nHouse temperature: " << houseTmp;
    return ss.str();
}


