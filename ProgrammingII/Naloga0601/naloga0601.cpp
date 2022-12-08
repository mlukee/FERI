#include "Canvas.h"
#include "Shape2D.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"

int main() {
    system(("chcp " + std::to_string(65001)).c_str());

    Canvas canvas;
    canvas.addShape(new Rectangle(ColorCode::Green, 5, 3));
    canvas.addShape(new Rectangle(ColorCode::Red, 3, 2));
    canvas.addShape(new Square(ColorCode::Blue, 5));
    canvas.addShape(new Square(ColorCode::Red, 3.4));
    canvas.addShape(new Rectangle(ColorCode::Default, 4.3, 6.5));
    canvas.addShape(new Triangle(ColorCode::Blue, 4));
    canvas.print();
}
