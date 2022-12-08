#include "Artist.h"
#include <sstream>
#include <iostream>

Artist::Artist(std::string name, std::string biography, Date dateOfBirth) : name(name), biography(biography), dateOfBirth(dateOfBirth) {}
Artist::Artist() : name("/"), biography("/"), dateOfBirth(dateOfBirth) {}
const std::string &Artist::getName() const{
    return name;
}

const std::string &Artist::getBiography() const{
    return biography;
}

Date Artist::getDate() const{
    return dateOfBirth;
}

std::string Artist::toString() const{
    std::stringstream ss;
    ss<<"Ime: " << name << "\nBiografija: " << biography << "\nDatum rojstva: " << dateOfBirth.toString();
    return ss.str();
}