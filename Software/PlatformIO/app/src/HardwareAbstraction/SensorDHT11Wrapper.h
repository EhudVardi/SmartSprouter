#ifndef SENSOR_DHT11_WRAPPER_H
#define SENSOR_DHT11_WRAPPER_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

class SensorDHT11Wrapper {
private:
    DHT dht;  // DHT sensor object

public:
    SensorDHT11Wrapper(int sensorPin) : dht(sensorPin, DHT11) {}

    void init() {
        dht.begin();
    }

    // read temperature in Celsius. return read result. value is passed by ref
    bool readTemperature(float &temperature) {
        temperature = dht.readTemperature();
        if (isnan(temperature))
            return false;
        return true;
    }
    // read humidity percentage. return read result. value is passed by ref
    bool readHumidity(float &humidity) {
        humidity = dht.readHumidity();
        if (isnan(humidity))
            return false;
        return true;
    }
};

#endif // SENSOR_DHT11_WRAPPER_H
