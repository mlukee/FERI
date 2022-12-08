#include "Guitar.h"
#include <iostream>
#include <sstream>

Guitar::Guitar(std::string id, std::string name, bool isPlaying, GuitarType type) : Instrument(id, name, isPlaying), type(type) {}

std::string Guitar::getGuitartTypeString() const {
    switch (type) {
        case GuitarType::Acustic:
            return "Acustic guitar";
        case GuitarType::Electric:
            return "Electric guitar";
        case GuitarType::Ukulele:
            return "Ukulele";
    }
}

std::string Guitar::makeSound() const {
    std::stringstream ss;
    if(getIsPlaying())
        ss << "\nGuitar " << getID() <<" is playing";
    else
        ss << "\nGuitar " << getID() << " is not playing";
    return ss.str();
}

std::string Guitar::toString() const{
    std::stringstream ss;
    ss << Instrument::toString() << "\nType: " << getGuitartTypeString() << (getIsPlaying() ? makeSound() : makeSound());
    return ss.str();
}


