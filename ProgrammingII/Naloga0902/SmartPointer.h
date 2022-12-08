#ifndef NALOGA0902_SMARTPOINTER_H
#define NALOGA0902_SMARTPOINTER_H

#include "Date.h"
#include "ReferenceCounter.h"
#include <ostream>

template<typename T>
class SmartPointer{
private:
    T* pData;
    ReferenceCounter* counter;
public:
    SmartPointer(T* pData) : pData(pData), counter(new ReferenceCounter()){
        (*counter)++;
    }
    ~SmartPointer(){
        if(--(*counter)==0){
            delete counter;
            delete pData;
        }
    }
    SmartPointer(const SmartPointer<T> &sp1) {
        if(this == &sp1)
            return;
        pData = sp1.pData;
        counter = sp1.counter;
        (*counter)++;
    }

    SmartPointer<T>& operator=(const SmartPointer<T> &other){
        if(this != &other){
            pData = other.pData;
            counter = other.counter;
            (*counter)++;
        }
        return *this;
    }

    unsigned int useCount() const { return counter->getCount(); }

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

#endif //NALOGA0902_SMARTPOINTER_H
