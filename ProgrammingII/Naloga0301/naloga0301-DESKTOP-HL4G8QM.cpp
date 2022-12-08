#include <iostream>
#include "Time.h"

int main() {
    std::cout << "-----------------------------\nPopoldne\n";
    Time popoldne {14, 45, 33};
    std::cout << popoldne.toString();
    std::cout << popoldne.toString12HourFormat();
    std::cout << "-----------------------------\nNarobe\n";
    Time narobe {66, 45,19};
    std::cout << narobe.toString();
    std::cout << narobe.toString12HourFormat();
    std::cout << "-----------------------------\nKopija Popoldne\n";
    Time *kopija = new Time(popoldne);
    std::cout << kopija->toString() << kopija->toString12HourFormat();
    std::cout << "-----------------------------\nisValid\n";
    Time * valid;
    std::cout << (valid->isTimeValid(24, 60, 55) ? "True " : "False")<<std::endl;
    std::cout << "-----------------------------\nParse\n";
    Time parse = parse.parse("24:23:23");
    std::cout << parse.toString();



    return 0;
}
