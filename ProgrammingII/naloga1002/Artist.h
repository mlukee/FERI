#ifndef NALOGA1002_ARTIST_H
#define NALOGA1002_ARTIST_H

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
    const std::string &getName() const;
    const std::string &getBiography() const;
    Date getDate() const;
    std::string toString() const;
};


#endif //NALOGA1002_ARTIST_H
