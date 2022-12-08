#include <iostream>
#include "Node.h"
#include "LinkedList.h"

int main() {
    LinkedList<int> list;
    std::cout << "List " << (list.isEmpty() ? "IS" : "IS NOT") << " empty." << std::endl << std::endl;
    list.add(1);
    list.add(4);
    list.add(10);
    list.removeAt(2);
    std::cout << "List " << (list.isEmpty() ? "IS" : "IS NOT") << " empty." << std::endl << std::endl;
    std::cout << "List (size " << list.getSize() << "): " << std::endl;
    for(int i=0; i<list.getSize(); i++)
        std::cout << list.at(i) << std::endl;

    std::cout << "\nList 2: \n";
    LinkedList<std::string> list2;
    list2.add("Matic");
    list2.add("Simon");
    list2.add("Gal");
    list2.add("Jure");
    list2.removeAt(0);

    for(int i=0;i<list2.getSize();i++){
        std::cout << list2.at(i) << (i != list2.getSize()-1 ? ", " : ".");
    }

    return 0;
}
