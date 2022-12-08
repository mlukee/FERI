#include <iostream>
#include <cmath>
#include <sstream>
#include "Square.h"
#include "PrintUtility.h"

Square::Square(ColorCode color, float a) : Shape2D(color), a(a) {}

float Square::getSurfaceArea() const {
    return a*a;
}

void Square::draw() const {
    for (int i = 1; i <= truncf(a); i++) {
        for (int j = 1; j <= truncf(a); j++) {
            PrintUtility::print(color, "* ");
        }
        std::cout << std::endl;
    }
    std::cout << toString();
}

std::string Square::toString() const {
    std::stringstream ss;
    ss << "a = " << a << std::endl;
    ss << "Ploscina: " << getSurfaceArea();
    return ss.str();
}