#include "SystemContext/SystemManagers/SensorManager.h"
#include "SystemContext/HWSystemPins/SensorPins.h"

bool SensorManager::initialize() {
    if (dht11Sensor == nullptr) {
        dht11Sensor = new SensorDHT11Wrapper(SENSOR_DHT11_PIN);
    }
    dht11Sensor->init();

    return true;
}

float SensorManager::getTemperature() {
    if (dht11Sensor) {
        return dht11Sensor->readTemperature();
    }
    return NAN;
}

float SensorManager::getHumidity() {
    if (dht11Sensor) {
        return dht11Sensor->readHumidity();
    }
    return NAN;
}
