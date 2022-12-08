#ifndef NALOGA0801_SPARSEMATRIX2D_H
#define NALOGA0801_SPARSEMATRIX2D_H
#include <vector>
#include "Element.h"

template<typename T>
class SparseMatrix2D{
private:
    std::vector<Element<T>> elements;
    unsigned int sizeX, sizeY;
    T defaultElement;
public:
    SparseMatrix2D(unsigned int sizeX, unsigned int sizeY, T defaultElement) : sizeX(sizeX), sizeY(sizeY), defaultElement(defaultElement){}

    void set(unsigned int x, unsigned int y, T value){
        if(x > sizeX || x < 0 || y > sizeY || y < 0)
            return;
        else{
            for(int i =0;i<elements.size();i++){
                if(elements[i].getX() == x && elements[i].getY() == y){
                    elements[i].setValue(value);
                    return;
                }
            }
            elements.push_back(Element<T>(x,y,value));
        }
    }

    T at(unsigned int x, unsigned int y) const{
        for(int i = 0; i< elements.size();i++){
            if (elements[i].getX()== x && elements[i].getY()==y)
                return elements[i].getValue();
        }
        return defaultElement;
    }

    void clearRow(int row){
        if(row >= sizeX)
            return;
        for(int i = elements.size()-1;i >= 0;i--){
            if(elements[i].getX() == row)
                elements.erase(elements.begin()+i);
        }
    }
    unsigned int getSizeX() const { return sizeX; }
    unsigned int getSizeY() const { return sizeY; }
};

#endif //NALOGA0801_SPARSEMATRIX2D_H
