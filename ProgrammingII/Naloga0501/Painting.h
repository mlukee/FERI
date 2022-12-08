#ifndef NALOGA0401_PAINTING_H
#define NALOGA0401_PAINTING_H

#include "Artwork.h"

enum class PaintingTechnique{
    Oil,
    Acrylic,
    Graphite
};

class Painting : public Artwork{
private:
    PaintingTechnique technique;
public:
    Painting(std::string title, std::string description, float price, int year, Artist* artist, PaintingTechnique pt);
    std::string getTechniqueTypeString() const;
    std::string toString() const override;
    void print() const;
};


#endif //NALOGA0401_PAINTING_H
