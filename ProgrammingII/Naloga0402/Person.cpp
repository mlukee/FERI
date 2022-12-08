//
// Created by Matic on 3/17/2022.
//

#include <sstream>
#include "Person.h"

Person::Person(std::string firstName, std::string lastName) : firstName(firstName), lastName(lastName) {}

std::string Person::getFirstName(){
    return firstName;
}
std::string Person::getLastName(){
    return lastName;
}

std::string Person::toString() {
    std::stringstream ss;
    ss<< firstName << " " << lastName;
    return ss.str();
}