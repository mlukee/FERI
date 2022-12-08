#include "SmartHome.h"
#include <sstream>
#include <vector>
#include <iostream>

SmartHome::SmartHome(std::string name) : name(name) {}

SmartHome::~SmartHome() {
    for(auto device : devices)
        delete device;
}

void SmartHome::addDevice(Device * device) {
    devices.push_back(device);
}

void SmartHome::printDevices() const{
    for(auto device : devices)
        std::cout << device->toString() << std::endl << std::endl;
}

std::string SmartHome::toString() const {
    std::stringstream ss;
    ss << "SmartHome name: " << name << std::endl;
    ss << "Devices:\n";
    for(auto device : devices)
        ss<< device->toString() << std::endl << std::endl;
    return ss.str();
}
