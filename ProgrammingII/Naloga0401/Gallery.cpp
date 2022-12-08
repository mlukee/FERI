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

void Gallery::removeArtwork(Artwork *artwork) {
    for (int i = 0; i < artworks.size(); i++) {
        if(artworks[i]->toString() == artwork->toString())
            artworks.erase(artworks.begin()+i);
    }
}

std::vector<Artwork*> Gallery::getArtworksBetweenYear(unsigned int startYear, unsigned int endYear) const{
    std::vector<Artwork*> getArtworks;
    for(int i = 0;i<artworks.size();i++){
        if(artworks[i]->getYear() >= startYear && artworks[i]->getYear() <= endYear)
            getArtworks.push_back(artworks[i]);
    }
    return getArtworks;
}

void Gallery::printArtworks() const{
    for (int i = 0; i < artworks.size(); ++i) {
        std::cout<< artworks[i]->toString() << std::endl << std::endl;
    }
}

std::string Gallery::toString() const {
    std::stringstream ss;
    ss<<"Name of the gallery: "<<name << std::endl;
    ss << "Artworks: \n";
    for (int i = 0; i < artworks.size(); i++) {
        ss<<artworks[i]->toString() << std::endl;
        ss << std::endl;
    }

    return ss.str();
}