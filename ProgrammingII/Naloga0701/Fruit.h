#ifndef NALOGA0701_FRUIT
#define NALOGA0701_FRUIT
#include <string>

class Fruit{
private:
    static unsigned int counter;
    std::string name;
    unsigned int calories;
public:
    Fruit();
    Fruit(std::string name, unsigned int calories);
    std::string toString() const;
};

#endif //NALOGA0701_FRUIT

