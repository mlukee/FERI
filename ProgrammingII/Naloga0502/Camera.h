#ifndef NALOGA0502_CAMERA_H
#define NALOGA0502_CAMERA_H

#include "Device.h"

class Camera : public Device {
private:
    std::string model;
public:
    Camera(std::string id, std::string name, std::string model);
    std::string toString() const override;
};
#endif //NALOGA0502_CAMERA_H
