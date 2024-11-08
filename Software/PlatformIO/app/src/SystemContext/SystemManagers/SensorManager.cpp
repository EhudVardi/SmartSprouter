#include "SensorManager.h"

bool SensorManager::initialize() {
    if (dht11Sensor == nullptr) {
        dht11Sensor = new SensorDHT11Wrapper(SENSOR_DHT11_PIN);
    }
    dht11Sensor->init();
    return true;
}
bool SensorManager::getTemperature(float &temperature) {
    if (dht11Sensor) {
        return dht11Sensor->readTemperature(temperature);
    }
    return false;
}
bool SensorManager::getHumidity(float &humidity) {
    if (dht11Sensor) {
        return dht11Sensor->readHumidity(humidity);
    }
    return false;
}
