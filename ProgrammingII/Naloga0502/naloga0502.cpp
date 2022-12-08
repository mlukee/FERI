#include <iostream>
#include "Device.h"
#include "Light.h"
#include "SmartHome.h"
#include "Camera.h"
#include "UnderFloorHeating.h"
#include "VentilatioSystem.h"

int main() {

    SmartHome *bajta = new SmartHome{"Smart Bajta"};
    Device *bedroomLight = new Light{"1", "Bedroom Light", 0};
    Device *diningRoomLight = new Light{"2", "Dinning Room Light", 1};
    Device *TV = new Device("13", "Bedroom TV");
    Device *frontDoorCamera = new Camera{"4", "Front Door Camera", "Blind Video Doorbell"};
    Device *backyardCamera = new Camera{"5", "Back yard camera", "Blind Video Doorbell"};
    Device *uFloorHeat = new UnderFloorHeating{"11", "Under floor heating", 19.8};
    Device * ventilation = new VentilationSystem{"334", "Ventilation system", 12, 16};

    bajta->addDevice(bedroomLight);
    bajta->addDevice(diningRoomLight);
    bajta->addDevice(TV);
    bajta->addDevice(frontDoorCamera);
    bajta->addDevice(backyardCamera);
    bajta->addDevice(uFloorHeat);
    bajta->addDevice(ventilation);

    bajta->printDevices();
    delete bajta;
    return 0;
}
