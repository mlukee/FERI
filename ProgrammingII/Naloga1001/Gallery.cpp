#include "Gallery.h"
#include <utility>
#include <algorithm>
#include "PrintIfPainting.h"

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
    for (auto &artwork : artworks) {
        ss<<artwork->toString() << std::endl << std::endl;
    }

    return ss.str();
}

void Gallery::sort(bool (*c)(Artwork *, Artwork*)){
    for(int i=0;i<artworks.size()-1;i++){
        for(int j = 0; j < artworks.size()-i-1;j++){
            if(!c(artworks[j], artworks[j+1]))
                std::swap(artworks[j], artworks[j+1]);
        }
    }
}

Artwork * Gallery::find(bool (*c)(Artwork *)) {
    auto it = std::find_if(artworks.begin(), artworks.end(), c);
    if(it != artworks.end())
        return *it;
}

std::vector<Artwork*> Gallery::findAll(bool (*c)(Artwork*)){
    std::vector<Artwork*> priceOver8k;
    for(auto &artwork : artworks){
        if(c(artwork))
            priceOver8k.push_back(artwork);
    }
    return priceOver8k;
}

void Gallery::printArtworks(PrintIfPainting i) const{
    std::for_each(artworks.begin(), artworks.end(), i);
}
