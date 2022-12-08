#include <iostream>
#include "SparseMatrix2D.h"
#include "Person.h"

int main() {

    SparseMatrix2D<Person> bigElementMatrix(5,5,Person("Matic"));
    bigElementMatrix.set(4,4,Person("Gal"));
    bigElementMatrix.set(0,0,Person("Jure"));
    bigElementMatrix.set(3,2, Person("Simon"));
    bigElementMatrix.set(0,3, Person("Vid"));
    bigElementMatrix.clearRow(0);

    for (int i = 0; i < bigElementMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigElementMatrix.getSizeY(); j++) {
            std::cout << bigElementMatrix.at(i,j).toString() << (j != bigElementMatrix.getSizeY() - 1 ? " ; " : "");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    // example for int
    SparseMatrix2D<int> bigIntMatrix(10, 10, 0);
    bigIntMatrix.set(5, 5, 8);
    bigIntMatrix.set(2, 3, 7);
    bigIntMatrix.set(2, 2, 4);
    bigIntMatrix.set(0,0,11);
    bigIntMatrix.set(11,11,20);
    bigIntMatrix.set(3,3,15);

    for (int i = 0; i < bigIntMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigIntMatrix.getSizeY(); j++) {
            std::cout << bigIntMatrix.at(i,j) << (j != bigIntMatrix.getSizeY() - 1 ? " ; " : "");
        }
        std::cout << std::endl;
    }
    std::cout << "\n\nAfter deleting: \n";

    bigIntMatrix.clearRow(2);
    for (int i = 0; i < bigIntMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigIntMatrix.getSizeY(); j++) {
            std::cout << bigIntMatrix.at(i,j) << (j != bigIntMatrix.getSizeY() - 1 ? " ; " : "");
        }
        std::cout << std::endl;
    }

    return 0;
}
