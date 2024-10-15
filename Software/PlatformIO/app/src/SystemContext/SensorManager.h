#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "BaseManager.h"

class SensorManager : public BaseManager {
public:
    bool initialize() override;
    void readSensors();  // Function to read from system sensors
};

#endif // SENSOR_MANAGER_H
