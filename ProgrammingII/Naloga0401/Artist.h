#ifndef NALOGA0401_ARTIST_H
#define NALOGA0401_ARTIST_H
#include "Date.h"
#include <string>

class Artist{
private:
    std::string name;
    std::string biography;
    Date dateOfBirth;
public:
    Artist();
    Artist(std::string name, std::string biography, Date dateOfBirth);
    std::string getName() const;
    std::string getBiography() const;
    Date getDate() const;
    std::string toString() const;
};


#endif //NALOGA0401_ARTIST_H
