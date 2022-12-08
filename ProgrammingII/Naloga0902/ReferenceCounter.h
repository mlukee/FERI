
#ifndef NALOGA0902_REFERENCECOUNTER_H
#define NALOGA0902_REFERENCECOUNTER_H

class ReferenceCounter{
private:
    unsigned int count;
public:
    ReferenceCounter():count(0){}
    unsigned int operator--(){ return --count; }
    unsigned int operator++(int dummy) { return count++; }
    unsigned int getCount() const { return count; }
    friend std::ostream &operator<<(std::ostream &out, const ReferenceCounter &counter){
        out << "Counter: " << counter.count;
        return out;
    }
};

#endif //NALOGA0902_REFERENCECOUNTER_H
