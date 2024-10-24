#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "BaseManager.h"

#include "HardwareAbstraction/SensorDHT11Wrapper.h"

class SensorManager : public BaseManager {
private:
    SensorDHT11Wrapper* dht11Sensor = nullptr;

public:
    bool initialize() override;
    float getTemperature();
    float getHumidity();
};

#endif // SENSOR_MANAGER_H
