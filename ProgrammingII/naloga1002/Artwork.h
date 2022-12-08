#ifndef NALOGA1001_ARTWORK_H
#define NALOGA1001_ARTWORK_H

#include "Artist.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

class Artwork{
protected:
    std::string title;
    std::string description;
    float price;
    int year;
    std::shared_ptr<Artist> artist;
public:
    Artwork(std::string title, std::string description, float price, int year, std::shared_ptr<Artist> artist);
    Artwork(const Artwork& t);
    std::string getTitle() const;
    std::string getDescription() const;
    float getPrice() const;
    int getYear() const;
    std::shared_ptr<Artist> getArtist() const;

    virtual std::string toString() const;
};
#endif //NALOGA1001_ARTWORK_H
