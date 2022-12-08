#include "Camera.h"
#include <sstream>

Camera::Camera(std::string id, std::string name, std::string model) : Device(id, name), model(model) {}

std::string Camera::toString() const {
    std::stringstream ss;
    ss<< Device::toString();
    ss << "\nModel: " << model;
    return ss.str();
}