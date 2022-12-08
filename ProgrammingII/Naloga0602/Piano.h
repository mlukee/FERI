#ifndef NALOGA0602_PIANO_H
#define NALOGA0602_PIANO_H

enum class PianoType{
    Console,
    Studio,
    Digital,
    Grand
};
#include "Instrument.h"
class Piano : public Instrument{
private:
    PianoType type;
public:
    Piano(std::string id, std::string name, bool isPlaying, PianoType type);
    std::string getPianoTypeString() const;
    std::string makeSound() const override;
    std::string toString() const override;
};


#endif //NALOGA0602_PIANO_H
