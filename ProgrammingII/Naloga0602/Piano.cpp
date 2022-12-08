#include <iostream>
#include <sstream>
#include "Piano.h"

Piano::Piano(std::string id, std::string name, bool isPlaying, PianoType type) : Instrument(id, name, isPlaying), type(type) {}

std::string Piano::getPianoTypeString() const {
    switch (type) {
        case PianoType::Console:
            return "Console piano";
        case PianoType::Studio:
            return "Studio piano";
        case PianoType::Digital:
            return "Digital piano";
        case PianoType::Grand:
            return "Grand piano";
    }
}

std::string Piano::makeSound() const {
    std::stringstream ss;
    if(Instrument::getIsPlaying())
        ss << "\nPiano " << getID() <<" is playing";
    else
        ss << "\nPiano " << getID() << " is not playing";
    return ss.str();
}

std::string Piano::toString() const {
    std::stringstream ss;
    ss << Instrument::toString() << "\nType: " << getPianoTypeString() << (getIsPlaying() ? makeSound() : makeSound());
    return ss.str();
}