#include <string>
#include <sstream>
#include "Time.h"

Time::Time(unsigned int hour, unsigned int minute, unsigned int second){
    if(!isTimeValid(hour, minute, second)){
        this->hour = 0;
        this->minute = 0;
        this->second = 0;
    }
    else{
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }
}

unsigned int Time::getHour() const{
    return hour;
}

unsigned int Time::getMinute() const {
    return minute;
}

unsigned int Time::getSecond() const {
    return second;
}

std::string Time::toString() const{
    std::stringstream ss;
    if(hour<10)
        ss<<"0";

    ss<<hour<<":";
    if(minute<10)
        ss<<"0";
    ss<<minute<<":";

    if(second<10)
        ss<<"0";
    ss<<second;
    return ss.str();
}

std::string Time::toString12HourFormat() const {
    std::stringstream ss;
    if(hour > noonHour){
        if(hour-noonHour<10)
            ss<<"0";
        ss<<hour-noonHour<<":";
        if(minute<10)
            ss<<"0";
        ss<<minute<<":";
        if(second<10)
            ss<<"0";
        ss<<second<<" PM";
        return ss.str();

    }else{
        ss<<toString()<<" AM"<<std::endl;
        return ss.str();
    }
}

bool Time::isTimeValid(unsigned int hour, unsigned int minute, unsigned int second){
    if(hour>maxHour || hour<0){
        return false;
    }else if(minute>60 || minute<0){
        return false;
    }else if(second>60 || second < 0)
        return false;
    else
        return true;
}

Time Time::parse(std::string time){
    int hour= stoi(time.substr(0,2));
    int minute = stoi(time.substr(3,2));
    int second = stoi(time.substr(6,2));

    return Time(hour, minute, second);
}

int Time::diffSeconds(const Time* time1, const Time* time2){
    int seconds1, seconds2 =0;

    seconds1 += time1->getSecond();
    seconds1 += time1->getHour()*3600;
    seconds1 += time1->getMinute()*60;

    seconds2 += time2->getSecond();
    seconds2 += time2->getHour()*3600;
    seconds2 += time2->getMinute()*60;

    return abs(seconds2- seconds1);
}


