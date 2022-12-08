#ifndef NALOGA0502_LIGHT_H
#define NALOGA0502_LIGHT_H

#include "Device.h"

class Light : public Device {
private:
    bool turnedOn;
public:
    Light(std::string id, std::string name, bool turnedOn);
    std::string toString() const override;
};


#endif //NALOGA0502_LIGHT_H
