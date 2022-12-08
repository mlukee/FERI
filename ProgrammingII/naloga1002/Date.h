#ifndef NALOGA1002_DATE_H
#define NALOGA1002_DATE_H

#include <string>

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
public:
    Date(unsigned int day , unsigned int month, unsigned int year);
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    std::string toString() const;
};



#endif //NALOGA1002_DATE_H
