#include "Device.h"
#include <sstream>
#include <iostream>

Device::Device(std::string id, std::string name) : id(id), name(name) {}

std::string Device::toString() const {
    std::stringstream ss;
    ss << "ID: " << id << "\nName: " << name;
    return ss.str();
}
