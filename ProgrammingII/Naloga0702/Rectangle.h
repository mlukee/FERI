#ifndef NALOGA0702_RECTANGLE_H
#define NALOGA0702_RECTANGLE_H

#include "Shape2D.h"
class Rectangle : public Shape2D {
private:
    float width, height;
public:
    Rectangle(ColorCode color,  float witdh, float  height);
    float getSurfaceArea() const override;
    void draw() const override;
    std::string toString() const override;
};

#endif //NALOGA0702_RECTANGLE_H