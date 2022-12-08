#include "Sculpture.h"

Sculpture::Sculpture(std::string title, std::string description, float price, int year, Artist* artist, float weight, Material material) : Artwork(title, description, price, year, artist), weight(weight), material(material){
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
