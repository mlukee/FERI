#include <iostream>
#include "Time.h"

int main() {

    std::cout << "-----------------------------\nPopoldne\n";
    Time popoldne {14, 45, 33};
    std::cout << popoldne.toString()<<std::endl;
    std::cout << popoldne.toString12HourFormat()<<std::endl;
    std::cout << "-----------------------------\nNarobe\n";
    Time narobe {23, 55,66};
    std::cout << narobe.toString()<<std::endl;
    std::cout << narobe.toString12HourFormat()<<std::endl;
    std::cout << "-----------------------------\nKopija Popoldne\n";
    Time *kopija = new Time(popoldne);
    std::cout << kopija->toString() <<std::endl << kopija->toString12HourFormat()<<std::endl;
    std::cout << "-----------------------------\nisValid\n";
    Time * valid;
    std::cout << (valid->isTimeValid(24, 60, 55) ? "True " : "False")<<std::endl;
    std::cout << "-----------------------------\nParse\n";
    Time parse = parse.parse("24:23:23");
    std::cout << parse.toString12HourFormat()<<std::endl;
    std::cout << "-----------------------------\nDiff seconds\n";
    std::cout<< "Diff seconds: " << Time::diffSeconds(&parse, &popoldne) << "s.";

    delete kopija;

    return 0;
}
