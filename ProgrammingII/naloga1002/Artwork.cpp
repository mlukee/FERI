#include <iostream>
#include <string>
#include "Artwork.h"
using std::string;

Artwork::Artwork(string title, string description, float price, int year, std::shared_ptr<Artist> artist) : title(title), description(description), price(price), year(year), artist(artist){}
Artwork::Artwork(const Artwork& t) : title(t.title), description(t.description), price(t.price), year(t.year){}

string Artwork::getTitle() const{
    return title;
}
string Artwork::getDescription() const {
    return description;
}
float Artwork::getPrice() const {
    return price;
}
int Artwork::getYear() const {
    return year;
}

std::shared_ptr<Artist> Artwork::getArtist() const{
    return artist;
}

string Artwork::toString() const{
    std::stringstream ss;
    ss << "Title: " << title << "\nDescription: " << description << "\nPrice: " << price <<"\nYear: " << year << "\nArtist: " << artist->getName();
    return ss.str();
}
