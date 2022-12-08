#ifndef NALOGA0602_GUITAR_H
#define NALOGA0602_GUITAR_H

#include "Instrument.h"
enum class GuitarType{
    Acustic,
    Electric,
    Ukulele
};
class Guitar : public Instrument{
private:
    GuitarType type;
public:
    Guitar(std::string id, std::string name, bool isPlaying, GuitarType type);
    std::string getName() const;
    std::string getGuitartTypeString() const;
    std::string makeSound() const override;
    std::string toString() const override;
};


#endif //NALOGA0602_GUITAR_H
