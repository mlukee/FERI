#ifndef NALOGA0401_GALLERY_H
#define NALOGA0401_GALLERY_H

#include "Artwork.h"
#include <vector>

class Gallery{
private:
    std::string name;
    std::vector<Artwork*> artworks;
public:
    Gallery(std::string name);
    std::string getName() const;
    std::vector<Artwork*> getArtworks() const;
    void addArtwork(Artwork * artwork);
    void printArtworks() const;
    std::string toString() const;
};


#endif //NALOGA0401_GALLERY_H
