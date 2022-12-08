#include "Date.h"
#include "UnparseableDateException.h"
#include <sstream>
#include <iostream>

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

bool goodDate(const std::string &date){
    int countDot = 0;
    int i = 0;
    char ch;
    if(date.size() < 8)
        return false;
    while(date[i]!='\0'){
        if(countDot > 2)
            return false;
        if(date[i]=='.')
            countDot++;
        ch = date[i];
        if((ch >= 'a' && ch<='z') ||(ch >= 'A' && ch<='Z'))
            return false;
        i++;
    }
    return true;
}

Date Date::GetDateFromString(const std::string &dateStr) {
    if(goodDate(dateStr)){
        unsigned int day,month,year;
        std::string tmpDate = dateStr;
        for(int i = 0;i<dateStr.size();i++){
            if(tmpDate[i]=='.')
                tmpDate[i] = ' ';
        }
        std::stringstream(tmpDate) >> day >> month >> year;
        return {day, month, year};
    }else{
        throw UnparseableDateException(dateStr);
    }
}

Date::Date() : day(0), month(0), year(0) {}

void Date::print() const {
    std::cout << toString() << std::endl;
}

