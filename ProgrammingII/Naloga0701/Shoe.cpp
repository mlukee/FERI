#include "Shoe.h"
#include <sstream>

Shoe::Shoe() : model("/"), firm("/"), size(0) {}

Shoe::Shoe(std::string model, std::string firm, float size) : model(model), firm(firm), size(size) {}

std::string Shoe::toString() const {
    std::stringstream ss;
    ss << "Model: " << model << "\nFirm: " << firm << "\nSize: " << size;
    return ss.str();
}