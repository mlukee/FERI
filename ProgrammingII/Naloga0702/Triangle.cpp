#include "Triangle.h"
#include "PrintUtility.h"
#include <iostream>
#include <math.h>
#include <sstream>

Triangle::Triangle(ColorCode color, float a) : Shape2D(color), a(a) {}

float Triangle::getSurfaceArea() const {
    return ((a*a)*sqrt(3))/4;
}

void Triangle::draw() const {
    for(int i = 1, k = 0; i <= a; ++i, k = 0){
        for(int space = 1; space <= a-i; ++space)
            std::cout <<"  ";
        while(k != 2*i-1){
            PrintUtility::print(color, "* ");
            ++k;
        }
        std::cout << std::endl;
    }
    std::cout << toString();
}

std::string Triangle::toString() const {
    std::stringstream ss;
    ss << "Stranica a: " << a << std::endl;
    ss << "Ploscina: " << getSurfaceArea();
    return ss.str();
}
