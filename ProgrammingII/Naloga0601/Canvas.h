#ifndef NALOGA0601_CANVAS_H
#define NALOGA0601_CANVAS_H

#include <vector>
#include "Shape2D.h"
class Canvas {
private:
    std::vector<Shape2D*> shapes;
public:
    ~Canvas();
    void addShape(Shape2D* shape);
    void print() const;
};


#endif //NALOGA0601_CANVAS_H
