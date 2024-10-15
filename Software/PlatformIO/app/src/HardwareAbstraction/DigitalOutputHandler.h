#ifndef DIGITAL_OUTPUT_HANDLER_H
#define DIGITAL_OUTPUT_HANDLER_H

#include <Arduino.h>
#include <map>
#include <vector>
#include <string>

class DigitalOutput {
private:
    int pin;

public:
    DigitalOutput() : pin(-1) {} // Default constructor to contain in a map
    DigitalOutput(int pin) : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    void set(int value) {
        digitalWrite(pin, value);
    }
};

class DigitalOutputHandler {
private:
    std::map<std::string, DigitalOutput> outputs;

public:
    DigitalOutputHandler(const std::vector<int>& pins, const std::vector<std::string>& names);
    void SetOutput(const std::string& name, int value);
    
};

#endif // DIGITAL_OUTPUT_HANDLER_H
