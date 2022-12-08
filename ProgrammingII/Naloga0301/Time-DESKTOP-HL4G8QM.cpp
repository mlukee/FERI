#include <string>
#include <iostream>
#include <sstream>
#include "Time.h"

Time::Time(unsigned int hour, unsigned int minute, unsigned int second){
    if(hour>this->maxHour){
        this->hour = 0;
        this->minute = 0;
        this->second = 0;
    }else{
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
    std::string myString;
    ss<<hour<<":"<<minute<<":"<<second<<std::endl;
    return myString = ss.str();
}

std::string Time::toString12HourFormat() const {
    std::stringstream ss;
    std::string myString;
    if(hour > noonHour){
        ss<<hour-noonHour<<":"<<minute<<":"<<second<<" PM"<<std::endl;
        return myString = ss.str();
    }else{
        ss<<hour<<":"<<minute<<":"<<second<<" AM"<<std::endl;
        return myString = ss.str();
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

Time Time::parse(const std::string &time){
    this->hour = stoi(time.substr(0,2));
    this->minute = stoi(time.substr(3,4));
    this->second = stoi(time.substr(6,7));
    //return {stoi(time.substr(0,2)), stoi(time.substr(3,4)), stoi(time.substr(6,7))};
}


