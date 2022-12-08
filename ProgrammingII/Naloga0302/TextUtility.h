#ifndef NALOGA0302_TEXTUTILITY_H
#define NALOGA0302_TEXTUTILITY_H

#include <string>

class TextUtility {
private:
    TextUtility();
public:
    static std::string capitalize(const std::string &str);
    static std::string toUpperCase(const std::string &str);
    static bool isNumeric(const std::string &str);
    static int contains(const std::string &str, const std::string &substr);
    static bool isPalindrome(const std::string &str);
    static std::string toLowerCase(const std::string &str);
    static std::string removeDoubleSpace(const std::string &str);
};


#endif //NALOGA0302_TEXTUTILITY_H
