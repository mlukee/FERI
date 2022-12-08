#ifndef NALOGA0702_PRINTUTILITY_H
#define NALOGA0702_PRINTUTILITY_H


#include "ColorCode.h"
#include <string>

class PrintUtility {
private:
    PrintUtility() = default;
public:
    static void print(const ColorCode &color, const std::string& str);
    static void print(const ColorCode &color, unsigned int n);
};


#endif //NALOGA0702_PRINTUTILITY_H
