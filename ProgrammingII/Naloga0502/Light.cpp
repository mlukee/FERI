#include <sstream>
#include <iostream>
#include "Light.h"

Light::Light(std::string id, std::string name, bool turnedOn) : Device(id, name), turnedOn(turnedOn) {}

std::string Light::toString() const {
    std::stringstream ss;
    ss<< Device::toString() << "\nTurned on: " << (turnedOn ? "Yes" : "No" );
    return ss.str();
}