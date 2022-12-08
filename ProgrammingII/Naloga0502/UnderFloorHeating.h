#ifndef NALOGA0502_UNDERFLOORHEATING_H
#define NALOGA0502_UNDERFLOORHEATING_H

#include "Device.h"

class UnderFloorHeating : public Device {
private:
    float houseTmp;
public:
    UnderFloorHeating(std::string id, std::string name, float houseTmp);
    std::string toString() const override;
};


#endif //NALOGA0502_UNDERFLOORHEATING_H
