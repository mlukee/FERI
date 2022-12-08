#include "Canvas.h"
#include "Shape2D.h"
#include "PrintUtility.h"
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include "Shoe.h"

template<ColorCode color = ColorCode::Green, typename T>
void printColor(std::vector<T> vec){
    for(auto &obj : vec){
        PrintUtility::print(color, obj);
        std::cout << std::endl;
    }
}

template<int n, typename T>
std::vector<std::vector<T>> slice(std::vector<T> vec){
    std::vector<std::vector<T>> slicedVec;
    std::vector<T> slice;
    for(int i = 0;i < vec.size();){
        slice.clear();
        for(int j = 0;j<n;j++){
            if(i >= vec.size())
                break;
            slice.push_back(vec[i]);
            i++;
        }
        slicedVec.push_back(slice);
    }
    return slicedVec;
}

template <typename T>
std::string toSafeString(std::vector<T> objects, std::vector<std::string> curseWords){
    std::string objToString, word, removedCursedWords, filtered;
    bool isCursed = false;
    int i;
    for(auto &obj : objects){
        objToString = obj.toString();
        std::istringstream ss(objToString);
        while(ss >> word){
            isCursed = false;
            for(auto &cursed : curseWords){
                i=0;
                filtered="";
                if(word == cursed) {
                    isCursed = true;
                    while (word[i] != '\0'){
                        filtered += '*';
                        i++;
                    }
                    removedCursedWords += filtered + " ";
                    break;
                }
            }
            if(!isCursed)
                removedCursedWords+=word + " ";
        }
        removedCursedWords +="\n";
    }
    return removedCursedWords;
}

template<typename T>
std::string removeVowels(const std::string& str, const std::vector<char>& vowels){
    std::string removedVowels;
    int i = 0;
    while(str[i] != '\0' || i >= str.length()){
        for(const auto vowel : vowels){
            if(str[i] == vowel) {
                i++;
                break;
            }
        }
        removedVowels+=str[i];
        i++;
    }
    return removedVowels;
}

template<typename T>
int numberOfVowels(const std::string& str, const std::vector<char>& vowels){
    int count = 0, i = 0;
    while(str[i] != '\0'){
        for(const auto vowel : vowels){
            if(str[i] == vowel){
                count++;
                break;
            }
        }
        i++;
    }
    return count;
}

template<ColorCode color = ColorCode::Red, typename T>
void printSelectedWordsInColor(const std::vector<T> &objects, const std::vector<std::string> &words){
    std::string objToString, word;
    bool isSelected = false;
    int i;
    for(auto &obj : objects){
        objToString = obj.toString();
        std::istringstream ss(objToString);
        while(ss >> word){
            isSelected = false;
            for(auto &selectedWord : words){
                i=0;
                if(word == selectedWord) {
                    isSelected = true;
                    PrintUtility::print(color, word);
                    std::cout << " ";
                    break;
                }
            }if(!isSelected){
                PrintUtility::print(ColorCode::Green, word);
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

template<typename T>
std::string toString(std::vector<T> vec) {
    std::stringstream ss;
    for (auto &obj: vec) {
        ss << obj.toString() << "\n";
    }
    return ss.str();
}

template<typename T>
void print(std::vector<T> &vec) {
    std::cout << toString(vec);
}

template<int N>
void fillDefault(std::vector<Shoe> &vec) {
    std::string firms[7] = {"Nike", "Adidas", "TH", "CK", "Guess", "Yeezi", "Vans"};
    std::string model[7] = {"Air force 99", "Air Force 98", "jet black", "randomnasd", "ok", "asdfdg", "aoo234"};
    for (int i = 0; i < N; i++)
        vec.push_back(Shoe(model[i % 7], firms[i % 7], (((float) i * 2.0f) + 3.0f)));
}


int main() {
    system(("chcp " + std::to_string(65001)).c_str());

    std::vector<std::string> names {"Matic", "Gal", "Jure", "Simon"};
    std::cout << std::endl <<"\nprintColor: \n";
    printColor<ColorCode::Blue>(names);
    std::cout << std::endl;
    printColor(names);
    std::cout << std::endl;

    std::vector<int> numbers {1,2,3,4,5,6,7,8,9,10};
    std::vector<std::vector<int>> sliced = slice<4>(numbers);
    for(int i = 0;i < sliced.size();i++){
        for(int j=0;j < sliced[i].size();j++){
            std::cout << sliced[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<Shoe> shoes;
    fillDefault<10>(shoes);
    std::vector<std::string> cursed {"GTFO", "Fuck", "Model", "Air", "Size:"};
    print(shoes);

    std::string removed = toSafeString(shoes, cursed);
    std::cout << "\n\nRemoved: \n" << removed;

    printSelectedWordsInColor(shoes, cursed);

    return 0;
}
