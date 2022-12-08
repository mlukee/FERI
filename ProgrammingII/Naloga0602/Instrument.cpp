#include "Instrument.h"
#include <sstream>
Instrument::Instrument(std::string id, std::string name, bool isPlaying) : id(id), name(name), isPlaying(isPlaying) {}

std::string Instrument::getID() const {
    return this->id;
}

bool Instrument::getIsPlaying() const{
    if(isPlaying)
        return true;
    return false;
}

std::string Instrument::toString() const {
    std::stringstream ss;
    ss<< "ID: " << id << "\nName: " << name;
    return ss.str();
}