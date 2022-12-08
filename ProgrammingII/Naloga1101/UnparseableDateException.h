#ifndef NALOGA1101_UNPARSEABLEDATEEXCEPTION_H
#define NALOGA1101_UNPARSEABLEDATEEXCEPTION_H


#include <exception>
#include <string>

class UnparseableDateException : public std::exception {
private:
    std::string message;
public:
    explicit UnparseableDateException(std::string message);
    const char* what() const noexcept override;
};


#endif //NALOGA1101_UNPARSEABLEDATEEXCEPTION_H
