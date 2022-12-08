#include "Gallery.h"
#include <utility>
#include <algorithm>
#include "PrintIfPainting.h"

Gallery::Gallery(std::string name) : name(name) {}

std::string Gallery::getName() const{
    return name;
}

std::vector<std::shared_ptr<Artwork>> Gallery::getArtworks() const{
    return artworks;
};

void Gallery::addArtwork(const std::shared_ptr<Artwork>& artwork) {
    this->artworks.push_back(artwork);
}

void Gallery::printArtworks() const{
    for (auto &artwork : artworks) {
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

void Gallery::sort(bool (*c)(std::shared_ptr<Artwork>, std::shared_ptr<Artwork>)) {
    for(int i=0;i<artworks.size()-1;i++){
        for(int j = 0; j < artworks.size()-i-1;j++){
            if(!c(artworks[j], artworks[j+1]))
                std::swap(artworks[j], artworks[j+1]);
        }
    }
}

std::shared_ptr<Artwork> Gallery::find(std::function<bool(std::shared_ptr<Artwork>)> c) const{
    auto it = std::find_if(artworks.begin(), artworks.end(), c);
    if(it != artworks.end())
        return *it;
    return artworks[0];
}

void Gallery::printArtworks(PrintIfPainting i) const{
    std::for_each(artworks.begin(), artworks.end(), i);
}


void Gallery::filterOut(const std::function<bool(std::shared_ptr<Artwork>)>& c){
 for(int i = 0; i< artworks.size(); i++){
     if(c(artworks[i])){
         artworks.erase(artworks.begin()+i);
         i--;
     }
 }
}