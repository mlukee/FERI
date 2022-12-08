#ifndef NALOGA0702_SHAPE2D_H
#define NALOGA0702_SHAPE2D_H


#include "ColorCode.h"
#include <string>

class Shape2D {
protected:
    ColorCode color;
public:
    Shape2D(ColorCode color);
    virtual float  getSurfaceArea() const = 0;
    virtual void draw() const = 0;
    virtual std::string toString() const = 0;
    void setColor(ColorCode clr);
};


#endif //NALOGA0702_SHAPE2D_H
