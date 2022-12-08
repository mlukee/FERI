#include <iostream>
#include <string>
#include "TextUtility.h"

int main() {
    std::string text = "lorem ipsum dolor, adipiscing magna? facil isi 2.5 morbi tempus urna id. Gravida non tellus orci! molestieac sed lectus.";
    std::cout<<"------------------------------------------\nTo upperCase:\n";
    std::cout<<TextUtility::toUpperCase(text);
    std::cout<<"------------------------------------------\nCapitalize:\n";
    std::cout<<TextUtility::capitalize(text);
    std::cout<<"------------------------------------------\nisNumeric: 0234a 5\n";
    std::cout<<((TextUtility::isNumeric("0234a 5")) ? "True" : "False")<<std::endl;
    std::cout<<"------------------------------------------\nisNumeric: 02345\n";
    std::cout<<((TextUtility::isNumeric("02345")) ? "True" : "False")<<std::endl;
    std::cout<<"------------------------------------------\nContains:\n";
    std::cout<<TextUtility::contains("Neobvezna naloga.", "goft")<<std::endl;
    std::cout<<"------------------------------------------\nContains:\n";
    std::cout<<TextUtility::contains("Lorem ipsum dolor.", "sum")<<std::endl;
    std::cout<<"------------------------------------------\nPalindrom Example1: Golf? No sir, prefer prison flog.\n";
    std::cout<<((TextUtility::isPalindrome("Golf? No sir, prefer prison flog."))? "True" : "False")<<std::endl;
    std::cout<<"------------------------------------------\nPalindrom Example2: pes\n";
    std::cout<<((TextUtility::isPalindrome("pes"))? "True" : "False")<<std::endl;
    std::cout<<"------------------------------------------\nToLowerCase\n";
    std::cout<< TextUtility::toLowerCase("Lorem ipsum dolor 12, adipiscin Magna.") << std::endl;
    std::cout<<"------------------------------------------\nRemoveDoubleSpace\n";
    std::cout<<TextUtility::removeDoubleSpace("     To  je    double    space.");

    return 0;
}
