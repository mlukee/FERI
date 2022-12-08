#ifndef NALOGA0902_DATE_H
#define NALOGA0902_DATE_H

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
    friend std::ostream& operator<<(std::ostream &out, const Date &date);
    bool operator==(const Date& other) const;
    Date& operator++();
    Date operator++(int dummy);
};


#endif //NALOGA0902_DATE_H
