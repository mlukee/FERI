#ifndef NALOGA0502_SMARTHOME_H
#define NALOGA0502_SMARTHOME_H


#include <string>
#include <vector>
#include "Device.h"

class SmartHome {
private:
    std::string name;
    std::vector<Device*> devices;
public:
    SmartHome(std::string name);
    ~SmartHome();
    void addDevice(Device * device);
    void printDevices() const;
    std::string toString() const;


};


#endif //NALOGA0502_SMARTHOME_H
