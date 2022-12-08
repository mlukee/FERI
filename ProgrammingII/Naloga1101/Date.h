#ifndef NALOGA1101_DATE_H
#define NALOGA1101_DATE_H

#include <string>

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
public:
    Date(unsigned int day , unsigned int month, unsigned int year);
    Date();
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    std::string toString() const;
    static Date GetDateFromString(const std::string& dateStr);
    void print() const;
};
#endif //NALOGA1101_DATE_H
