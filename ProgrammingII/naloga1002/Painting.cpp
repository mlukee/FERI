#include "Painting.h"

#include <utility>
#include <memory>

Painting::Painting(std::string title, std::string description, float price, int year, std::shared_ptr<Artist> artist,
                   PaintingTechnique pt) :
        Artwork(std::move(title), std::move(description), price, year, std::move(artist)), technique(pt) {}

std::string Painting::getTechniqueTypeString() const{
    switch(technique){
        case PaintingTechnique::Oil:
            return "Oil";
        case PaintingTechnique::Acrylic:
            return "Acrylic";
        case PaintingTechnique::Graphite:
            return "Graphite";
        default:
            return "?";
    }
}

std::string Painting::toString() const {
    std::stringstream ss;
    ss << Artwork::toString() << "\nPainting Technique: " << getTechniqueTypeString();
    return ss.str();
}

void Painting::print() const {
    std::cout << this->toString();
}
