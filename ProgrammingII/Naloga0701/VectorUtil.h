#ifndef NALOGA0701_VECTORUTIL_H
#define NALOGA0701_VECTORUTIL_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Fruit.h"
#include "Shoe.h"

template<int N, typename T>
void fillDefault(std::vector<T> &vec) {
    for (int i = 0; i < N; i++)
        vec.push_back(T());
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

template<typename T>
std::vector<T> reverse(std::vector<T> &vec) {
    std::vector<T> reversed;
    for (int i = vec.size() - 1; i >= 0; i--) {
        reversed.push_back(vec[i]);
    }
    return reversed;
}

template<int N>
void fillDefault(std::vector<Shoe> &vec) {
    std::string firms[7] = {"Nike", "Adidas", "TH", "CK", "Guess", "Yeezi", "Vans"};
    std::string model[7] = {"Air force 99", "Air Force 98", "jet black", "randomnasd", "ok", "asdfdg", "aoo234"};
    for (int i = 0; i < N; i++)
        vec.push_back(Shoe(model[i % 7], firms[i % 7], (((float) i * 2.0f) + 3.0f)));
}

template<typename T>
std::vector<T> mergeLists(std::vector<std::vector<T>> vec) {
    std::vector<T> merged;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            merged.push_back(vec[i][j]);
        }
    }
    return merged;
}

std::string mergeLists(std::vector<std::string> vec) {
    std::string mergedStr;
    for (int i = 0; i < vec.size(); i++) {
        mergedStr += vec[i];
    }
    return mergedStr;
}


#endif //NALOGA0701_VECTORUTIL_H
