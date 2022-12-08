#include "Date.h"
#include <sstream>

Date::Date(unsigned int day , unsigned int month, unsigned int year): day(day), month(month), year(year){}

unsigned int Date::getDay() const{
    return day;
}

unsigned int Date::getMonth() const{
    return month;
}

unsigned int Date::getYear() const{
    return month;
}

std::string Date::toString() const{
    std::stringstream ss;
    ss<< day << "." << month << "." << year;
    return ss.str();
}