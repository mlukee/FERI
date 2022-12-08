#include "Rectangle.h"
#include <iostream>
#include <sstream>
#include <cmath>

Rectangle::Rectangle(float witdh, float height) : width(witdh), height(height) {}

float Rectangle::getSurfaceArea() const {
    return width * height;
}

std::string Rectangle::toString() const {
    std::stringstream ss;
    ss << "Width: " << width << "\nHeight: " << height;
    return ss.str();
}

Rectangle &Rectangle::operator--(){
    this->width--;
    this->height--;
    return *this;
}

Rectangle Rectangle::operator--(int dummy) {
    Rectangle tmp(*this);
    --*this;
    return tmp;
}

std::ostream &operator<<(std::ostream &out, const Rectangle &rec) {
    out << rec.toString();
    return out;
}