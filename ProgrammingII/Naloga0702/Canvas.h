#ifndef NALOGA0702_CANVAS_H
#define NALOGA0702_CANVAS_H


#include <vector>
#include "Shape2D.h"
class Canvas {
private:
    std::vector<Shape2D*> shapes;
public:
    ~Canvas();
    void addShape(Shape2D* shape);
    std::vector<Shape2D*> getShapes();
    void print() const;
};


#endif //NALOGA0702_CANVAS_H
