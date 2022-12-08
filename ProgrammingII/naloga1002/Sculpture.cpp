#include "Sculpture.h"

#include <utility>

Sculpture::Sculpture(std::string title, std::string description, float price, int year, std::shared_ptr<Artist> artist, float weight, Material material) : Artwork(std::move(title), std::move(description), price, year, std::move(artist)), weight(weight), material(material){
}

std::string Sculpture::getMaterial() const{
    switch(material){
        case Material::Wood:
            return "Wood";
        case Material::Stone:
            return "Stone";
        case Material::Metal:
            return "Metal";
        case Material::Clay:
            return "Clay";
        default:
            return "?";
    }
}
std::string Sculpture::toString() const{
    std::stringstream ss;
    ss << Artwork::toString() << "\nWeight: " << weight <<" kg\nMaterial: " << getMaterial();
    return ss.str();
}
void Sculpture::print() const{
    std::cout << toString();
}
