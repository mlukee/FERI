#ifndef NALOGA0201_ARTWORK_H
#define NALOGA0201_ARTWORK_H

#include "Artist.h"
#include <iostream>
#include <sstream>
#include <string>


class Artwork{
private:
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
    void setTitle(const std::string &title);
    void setDescription(const std::string &description);
    void setPrice(float price);
    void setYear(int year);
    std::string toString() const;
};

#endif //NALOGA0201_ARTWORK_H
