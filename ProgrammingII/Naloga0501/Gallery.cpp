#include "Gallery.h"

Gallery::Gallery(std::string name) : name(name) {}

std::string Gallery::getName() const{
    return name;
}

std::vector<Artwork*> Gallery::getArtworks() const{
    return artworks;
};

void Gallery::addArtwork(Artwork *artwork) {
    artworks.push_back(artwork);
}

void Gallery::printArtworks() const{
    for (auto artwork : artworks) {
        std::cout<< artwork->toString() << std::endl << std::endl;
    }
}

std::string Gallery::toString() const {
    std::stringstream ss;
    ss<<"Name of the gallery: "<<name << std::endl;
    ss << "Artworks: \n";
    for (auto artwork : artworks) {
        ss<<artwork->toString() << std::endl << std::endl;
    }

    return ss.str();
}