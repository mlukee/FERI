
#ifndef NALOGA0601_SQUARE_H
#define NALOGA0601_SQUARE_H

#include "Shape2D.h"

class Square : public Shape2D{
private:
    float a;
public:
    Square(ColorCode color, float a);
    float getSurfaceArea() const override;
    void draw() const override;
    std::string toString() const override;
};


#endif //NALOGA0601_SQUARE_H
