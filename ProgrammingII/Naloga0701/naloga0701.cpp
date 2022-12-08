#include <iostream>
#include "Fruit.h"
#include "Shoe.h"
#include "VectorUtil.h"
#include <vector>illDefault<10>(list);
int main() {
    std::vector<Fruit> list;
    std::cout << "Default generator of 10 objects" << std::endl;

    std::cout << "Prints by using toString function" << std::endl;
    print(list);
    //::cout << toString(list);

    std::cout << "Return new list with Reversed  order" << std::endl;
    std::vector<Fruit> list2 = reverse(list);
    print(list2);

    std::vector<Shoe> shoes;
    fillDefault<10>(shoes);
    print(shoes);
    std::vector<std::string> words {"Jure ", "Luka ", "Gal "};
    std::string merged = mergeLists(words);
    std::cout << "\nMerged to string: \n\n" << merged;
    return 0;
}
template <typename T>
float divide(T a, T b){
    return a/b;
}

for(int i =0 ; i<vec.size();i++)
    std::cout << vec[i];

for(auto& it : vec)
    std::cout << it;
