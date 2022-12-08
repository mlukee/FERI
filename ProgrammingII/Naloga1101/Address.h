#ifndef NALOGA1101_ADDRESS_H
#define NALOGA1101_ADDRESS_H
#include <string>

class Address {
private:
    std::string street, post, country;
public:
    Address(std::string street, std::string post, std::string country);
    std::string toString() const;
};


#endif //NALOGA1101_ADDRESS_H
