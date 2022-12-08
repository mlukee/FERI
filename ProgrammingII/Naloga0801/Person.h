#ifndef NALOGA0801_PERSON_H
#define NALOGA0801_PERSON_H

#include <string>
class Person {
private:
    std::string name;
public:
    Person(std::string n) : name(n) {}
    std::string toString() const{
        std::stringstream ss;
        ss << name;
        return ss.str();
    }
};

#endif //NALOGA0801_PERSON_H
