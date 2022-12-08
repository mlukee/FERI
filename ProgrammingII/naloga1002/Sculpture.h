#ifndef NALOGA1002_SCULPTURE_H
#define NALOGA1002_SCULPTURE_H

#include "Artwork.h"
#include <memory>

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
    Sculpture(std::string title, std::string description, float price, int year, std::shared_ptr<Artist> artist, float weight, Material material);
    std::string getMaterial() const;
    std::string toString() const override;
    void print() const;
};


#endif //NALOGA1002_SCULPTURE_H
