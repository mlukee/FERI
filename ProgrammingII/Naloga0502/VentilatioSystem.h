
#ifndef NALOGA0502_VENTILATIOSYSTEM_H
#define NALOGA0502_VENTILATIOSYSTEM_H

#include "Device.h"
class VentilationSystem : public Device {
private:
    unsigned int startHour, endHour;
public:
    VentilationSystem(std::string id, std::string name, unsigned int startHour, unsigned int endHour);
    std::string toString() const override;
};


#endif //NALOGA0502_VENTILATIOSYSTEM_H
