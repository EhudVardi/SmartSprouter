#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/SensorDHT11Wrapper.h"

class SensorManager : public BaseManager {
private:
    SensorDHT11Wrapper* dht11Sensor = nullptr;

public:
    bool initialize() override;
    bool getTemperature(float& temperature);
    bool getHumidity(float& humidity);
};

#endif // SENSOR_MANAGER_H
