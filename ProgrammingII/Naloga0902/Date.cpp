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

bool Date::operator==(const Date &other) const{
    if(this == &other)
        return true;
    if((this->day == other.day) && (this->month == other.month) && (this->year == other.year))
        return true;
    return false;
}

Date &Date::operator++() {
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(day+1 > months[getMonth()-1]){ //ce je st dnevov vec kot st dnevov v dolocenem mesecu
        this->day = 1;
        if(this->month == 12){ //novo leto
            this->month = 1;
            this->year++;
        }else{
            month++;
        }
    }
    else
        this->day++;
    return *this;
}

Date Date::operator++(int dummy) {
    Date tmp(*this);
    ++*this;
    return tmp;
}

std::ostream &operator<<(std::ostream &out, const Date &date) {
    out << date.toString();
    return out;
}


