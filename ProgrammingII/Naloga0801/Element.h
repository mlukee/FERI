#ifndef NALOGA0801_ELEMENT_H
#define NALOGA0801_ELEMENT_H

#include <string>
#include <sstream>

template<typename T>
class Element{
private:
    unsigned int x, y;
    T value;
public:
    Element(unsigned int x, unsigned int y, T value) : x(x), y(y), value(value){}
    void setX(unsigned int X) { x = X; }
    void setY(unsigned int Y) { y = Y; }
    void setValue(T Value) { value = Value; }
    unsigned int getX() const { return x; }
    unsigned int getY() const { return y; }
    T getValue() const { return value; }
    std::string toString() const{
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
};

#endif //NALOGA0801_ELEMENT_H
