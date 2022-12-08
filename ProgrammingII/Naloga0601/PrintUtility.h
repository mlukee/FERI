#ifndef TASK0601_PRINTUTILITY_H
#define TASK0601_PRINTUTILITY_H

#include "ColorCode.h"
#include <string>

class PrintUtility {
private:
    PrintUtility() = default;
public:
    static void print(const ColorCode &color, const std::string& str);
    static void print(const ColorCode &color, unsigned int n);
};


#endif //TASK0601_PRINTUTILITY_H
