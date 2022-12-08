#ifndef NALOGA0901_SMARTPOINTER_H
#define NALOGA0901_SMARTPOINTER_H

#include "Date.h"

template<typename T>
class SmartPointer{
private:
    T* pData;
public:
    SmartPointer(T* pData) : pData(pData){}

    ~SmartPointer(){
        delete pData;
    }
    T& operator*(){
        return *pData;
    }
    T* operator->(){
        return pData;
    }
    std::string toString() const{
        return pData->toString();
    }
};

#endif //NALOGA0901_SMARTPOINTER_H
