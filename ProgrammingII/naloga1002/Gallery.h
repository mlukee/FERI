#ifndef NALOGA1002_GALLERY_H
#define NALOGA1002_GALLERY_H

#include "Artwork.h"
#include "PrintIfPainting.h"
#include <vector>
#include <memory>
#include <functional>

class Gallery{
private:
    std::string name;
    std::vector<std::shared_ptr<Artwork>> artworks;
public:
    Gallery(std::string name);
    std::string getName() const;
    std::vector<std::shared_ptr<Artwork>> getArtworks() const;
    void addArtwork(const std::shared_ptr<Artwork>& artwork);
    void printArtworks() const;
    std::string toString() const;
    void sort(bool (*c)(std::shared_ptr<Artwork>, std::shared_ptr<Artwork>));
    std::shared_ptr<Artwork> find(std::function<bool(std::shared_ptr<Artwork>)> c) const;
    void printArtworks(PrintIfPainting i) const;
    void filterOut(const std::function<bool(std::shared_ptr<Artwork>)>& c);
};

#endif //NALOGA1002_GALLERY_H
