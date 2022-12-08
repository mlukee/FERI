#include "Fruit.h"
#include <sstream>

unsigned int Fruit::counter = 1;
Fruit::Fruit(){
    name = "x" + std::to_string(counter);
    calories = counter * 0.5 * 4;
    counter++;
}

Fruit::Fruit(std::string name, unsigned int calories) : name(name), calories(calories) {}

std::string Fruit::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << "\n Calories: " << calories;
    return ss.str();
}
