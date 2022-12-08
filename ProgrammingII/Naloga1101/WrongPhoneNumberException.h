//
// Created by Asus on 31. 05. 2022.
//

#ifndef NALOGA1101_WRONGPHONENUMBEREXCEPTION_H
#define NALOGA1101_WRONGPHONENUMBEREXCEPTION_H

#include <exception>
#include <string>
class WrongPhoneNumberException : public std::exception{
private:
    std::string message;
public:
    explicit WrongPhoneNumberException(std::string msg);
    const char* what() const noexcept override;
};


#endif //NALOGA1101_WRONGPHONENUMBEREXCEPTION_H
