#ifndef NALOGA0901_RECTANGLE_H
#define NALOGA0901_RECTANGLE_H

#include <string>
#include <ostream>

class Rectangle{
private:
    float width, height;
public:
    Rectangle(float witdh, float  height);
    float getSurfaceArea() const;
    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &out, const Rectangle &rec);
    Rectangle& operator--();
    Rectangle operator--(int dummy);
};


#endif //NALOGA0901_RECTANGLE_H
