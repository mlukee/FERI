#include "TextUtility.h"
#include <iostream>
#include <string>
TextUtility::TextUtility() {}

std::string TextUtility::capitalize(const std::string &str) {
    int i=0;
    char c;
    std::string myString = str;
    while(myString[i]){
        if(i==0){
            c=myString[0];
            myString[0] = toupper(c);
        }else if(myString[i]=='.' && myString[i+1]==' '  && i+1 != myString.length()){
                c=myString[i+2];
                myString[i+2] = toupper(c);
        }else if(myString[i]=='?' && myString[i+1]==' ' && i+1 != myString.length()){
                c=myString[i+2];
                myString[i+2] = toupper(c);
        }else if(myString[i]=='!' && myString[i+1]==' ' && i+1 != myString.length()){
                c=myString[i+2];
                myString[i+2] = toupper(c);
        }
        i++;
    }
    return myString;
}

std::string TextUtility::toUpperCase(const std::string &str){
   int i=0;
   char c;
   std::string myString="";
   while(str[i]){
       c=str[i];
       myString+=(toupper(c));
       i++;
   }
   return myString;
}

bool TextUtility::isNumeric(const std::string &str) {
    int i=0;
    bool isNumber= true;
    char c;
    while(str[i] || !isNumber){
        c=str[i];
        if(std::isdigit(c) == 0) {
            isNumber=false;
            return isNumber;
        }
        i++;
    }
    return isNumber;
}

int TextUtility::contains(const std::string &str, const std::string &substr){
    int i=0;
    int index = 0;
    std::string compare ="";
    while(str[i]){
        if(str[i]==substr[0]){
            index= i;
            for(int j=0;j<substr.length() || index!=str.length();j++) {
                if (str[index] != substr[j])
                    break;
                compare+=substr[j];
                index++;
            }
            if(compare==substr)
                return i;
        }
        compare="";
        i++;
    }
    return -1;
}

bool TextUtility::isPalindrome(const std::string &str){
    std::string tempStr = "";
    int i=0;
    char c;
    while(str[i]){
        c = str[i];
        if(std::isupper(c))
            tempStr+= tolower(c);
        else if(std::islower(c))
            tempStr+=c;
        i++;
    }
    i=0;
    int j=tempStr.length()-1;
    while(tempStr[i]){
        if(tempStr[i] != tempStr[j])
            return false;
        i++;
        j--;
    }
    return true;
}

std::string TextUtility::toLowerCase(const std::string &str) {
    int i=0;
    char c;
    std::string myString="";
    while(str[i]){
        c=str[i];
        myString+=(tolower(c));
        i++;
    }
    return myString;
}

std::string TextUtility::removeDoubleSpace(const std::string &str){
    int i=0;
    char c;
    std::string myString="";

    while(str[i] == ' ') i++;

    while(str[i]){
        if(str[i] == ' '){
            while(str[i] == ' ')
                i++;
            c=str[i];
            myString =myString + " ";
        }else
            c=str[i];
        myString+=c;
        i++;
    }
    return myString;
}



