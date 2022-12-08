#ifndef NALOGA0301_TIME_H
#define NALOGA0301_TIME_H


class Time {
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    const static int maxHour = 24;
    const static int noonHour = 12;
public:
    Time(unsigned int hour, unsigned int minute, unsigned int second);
    unsigned int getHour() const;
    unsigned int getMinute() const;
    unsigned int getSecond() const;
    std::string toString() const;
    std::string toString12HourFormat() const;
    static bool isTimeValid(unsigned int hour, unsigned int minute, unsigned int second);
    static Time parse(std::string time);
    static int diffSeconds(const Time* time1, const Time* time2);
};


#endif //NALOGA0301_TIME_H
