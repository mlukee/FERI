#ifndef NALOGA0602_CONCERT_H
#define NALOGA0602_CONCERT_H

#include <vector>
#include "Instrument.h"

class Concert {
private:
    std::string name;
    std::vector<Instrument*> instruments;
public:
    Concert(std::string name);
    ~Concert();
    std::string getName() const;
    void addInstrument(Instrument * instrument);
    void printAllInstruments() const;
    std::string toString() const;
};


#endif //NALOGA0602_CONCERT_H
