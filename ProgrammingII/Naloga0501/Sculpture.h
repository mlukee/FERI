
#ifndef NALOGA0401_SCULPTURE_H
#define NALOGA0401_SCULPTURE_H
#include "Artwork.h"

enum class Material {
    Wood,
    Stone,
    Metal,
    Clay
};

class Sculpture : public Artwork {
private:
    float weight;
    Material material;
public:
    Sculpture(std::string title, std::string description, float price, int year, Artist* artist, float weight, Material material);
    std::string getMaterial() const;
    std::string toString() const override;
    void print() const;
};


#endif //NALOGA0401_SCULPTURE_H
