#include <iostream>
#include "Canvas.h"

Canvas::~Canvas() {
    for(auto &shape : shapes)
        delete shape;
}
void Canvas::addShape(Shape2D *shape) {
    shapes.push_back(shape);
}

void Canvas::print() const {
    for (auto &shape: shapes) {
        shape->draw();
        std::cout << std::endl << std::endl;
    }
}
