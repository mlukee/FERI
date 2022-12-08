#include "Rectangle.h"
#include "PrintUtility.h"
#include <iostream>
#include <sstream>
#include <cmath>

Rectangle::Rectangle(ColorCode color, float witdh, float height) : Shape2D(color), width(witdh), height(height) {}

float Rectangle::getSurfaceArea() const {
    return width*height;
}
void Rectangle::draw() const {
    for (int i = 1; i <= truncf(height); i++) {
        for (int j = 1; j <= truncf(width); j++) {
            PrintUtility::print(color, "* ");
        }
        std::cout << std::endl;
    }
    std::cout << toString();
}


std::string Rectangle::toString() const {
    std::stringstream ss;
    ss << "a = " << width << "\nb = " << height << std::endl;
    ss << "Ploscina: " << getSurfaceArea();
    return ss.str();
}