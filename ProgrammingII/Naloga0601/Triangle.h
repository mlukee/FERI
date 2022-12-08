//
// Created by Asus on 5. 04. 2022.
//

#ifndef NALOGA0601_TRIANGLE_H
#define NALOGA0601_TRIANGLE_H

#include "Shape2D.h"
#include <string>

class Triangle : public Shape2D {
private:
    float a;
public:
    Triangle(ColorCode color, float a);
    float getSurfaceArea() const override;
    void draw() const override;
    std::string toString() const override;
};


#endif //NALOGA0601_TRIANGLE_H
