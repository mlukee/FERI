#ifndef NALOGA1001_GALLERY_H
#define NALOGA1001_GALLERY_H

#include "Artwork.h"
#include "PrintIfPainting.h"
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
    void sort(bool (*c)(Artwork *, Artwork*));
    Artwork * find(bool (*c)(Artwork *));
    std::vector<Artwork*> findAll(bool (*c)(Artwork*));
    void printArtworks(PrintIfPainting i) const;
};


#endif //NALOGA1001_GALLERY_H
