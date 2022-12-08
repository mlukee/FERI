#ifndef NALOGA1002_PAINTING_H
#define NALOGA1002_PAINTING_H

#include "Artwork.h"
#include <memory>

enum class PaintingTechnique{
    Oil,
    Acrylic,
    Graphite
};

class Painting : public Artwork{
private:
    PaintingTechnique technique;
public:
    Painting(std::string title, std::string description, float price, int year, std::shared_ptr<Artist> artist, PaintingTechnique pt);
    std::string getTechniqueTypeString() const;
    std::string toString() const override;
    void print() const;
};


#endif //NALOGA1002_PAINTING_H
