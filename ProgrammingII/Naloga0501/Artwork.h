#ifndef NALOGA0201_ARTWORK_H
#define NALOGA0201_ARTWORK_H

#include "Artist.h"
#include <iostream>
#include <sstream>
#include <string>


class Artwork{
protected:
    std::string title;
    std::string description;
    float price;
    int year;
    Artist* artist;
public:
    Artwork(std::string title, std::string description, float price, int year, Artist* artist);
    Artwork(const Artwork& t);
    std::string getTitle() const;
    std::string getDescription() const;
    float getPrice() const;
    int getYear() const;
    Artist* getArtist() const;

    virtual std::string toString() const = 0;
};

#endif //NALOGA0201_ARTWORK_H
