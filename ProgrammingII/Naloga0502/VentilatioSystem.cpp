#include "VentilatioSystem.h"
#include <sstream>
VentilationSystem::VentilationSystem(std::string id, std::string name, unsigned int startHour, unsigned int endHour) : Device(id, name), startHour(startHour), endHour(endHour){
}
std::string VentilationSystem::toString() const {
    std::stringstream ss;
    ss << Device::toString() << "\nStart hour: " << startHour << "\nEnd Hour: " << endHour;
    return ss.str();
}
