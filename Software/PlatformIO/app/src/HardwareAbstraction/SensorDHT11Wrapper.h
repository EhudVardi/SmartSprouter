#ifndef SENSOR_DHT11_WRAPPER_H
#define SENSOR_DHT11_WRAPPER_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

class SensorDHT11Wrapper {
private:
    DHT dht;  // DHT sensor object

public:
    // Constructor that initializes the DHT object with the sensor pin
    SensorDHT11Wrapper(int sensorPin) : dht(sensorPin, DHT11) {}

    // Initialize the DHT sensor (to be called in setup)
    void init() {
        dht.begin();
    }

    // Function to read temperature in Celsius
    float readTemperature() {
        return dht.readTemperature(); // Return temperature as float
    }

    // Function to read humidity percentage
    float readHumidity() {
        return dht.readHumidity(); // Return humidity as float
    }
};

#endif // SENSOR_DHT11_WRAPPER_H
