#ifndef NALOGA0702_SHOE_H
#define NALOGA0702_SHOE_H


#include <string>

class Shoe {
private:
    std::string model, firm;
    float size;
public:
    Shoe();
    Shoe(std::string model, std::string firm, float size);
    std::string toString() const;
};


#endif //NALOGA0702_SHOE_H
