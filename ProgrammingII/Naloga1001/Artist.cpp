#include "Artist.h"
#include <sstream>

Artist::Artist(std::string name, std::string biography, Date dateOfBirth) : name(name), biography(biography), dateOfBirth(dateOfBirth) {}
Artist::Artist() : name("/"), biography("/"), dateOfBirth(dateOfBirth) {}
std::string Artist::getName() const{
    return name;
}

std::string Artist::getBiography() const{
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