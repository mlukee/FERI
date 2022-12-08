
#include "WrongPhoneNumberException.h"
 WrongPhoneNumberException::WrongPhoneNumberException(std::string msg) : message("Wrong phone number: " + msg){}

const char *WrongPhoneNumberException::what() const noexcept {
    return message.c_str();
}
