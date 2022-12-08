#ifndef NALOGA0402_PERSON_H
#define NALOGA0402_PERSON_H

#include <string>
#include "Date.h"

class Person{
private:
    std::string firstName;
    std::string lastName;
public:
    Person(std::string firstName, std::string lastName);
    std::string getFirstName();
    std::string getLastName();
    std::string toString();
};


#endif //NALOGA0402_PERSON_H
