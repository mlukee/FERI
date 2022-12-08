#ifndef NALOGA0602_INSTRUMENT_H
#define NALOGA0602_INSTRUMENT_H

#include <string>

class Instrument {
private:
    std::string id;
    std::string name;
    bool isPlaying;
public:
    Instrument(std::string id, std::string name, bool isPlaying);
    std::string getID() const;
    bool getIsPlaying() const;
    virtual std::string makeSound() const = 0;
    virtual std::string toString() const;
};


#endif //NALOGA0602_INSTRUMENT_H
