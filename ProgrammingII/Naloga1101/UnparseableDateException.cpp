#include "UnparseableDateException.h"

const char * UnparseableDateException::what() const noexcept {
    return message.c_str();
}

UnparseableDateException::UnparseableDateException(std::string message) : message("Unparseable date: " + message + "."){}
