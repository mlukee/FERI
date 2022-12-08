#include <iostream>
#include <sstream>
#include "Concert.h"

Concert::Concert(std::string name) : name(name) {}

Concert::~Concert() {
    for(auto &instrument : instruments)
        delete instrument;
}

std::string Concert::getName() const{
    return this->name;
}

void Concert::addInstrument(Instrument * instrument) {
    instruments.push_back(instrument);
}

void Concert::printAllInstruments() const {
    for (auto &instrument: instruments)
        std::cout << instrument->toString() << std::endl << std::endl;
}

std::string Concert::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << std::endl;
    return ss.str();
}