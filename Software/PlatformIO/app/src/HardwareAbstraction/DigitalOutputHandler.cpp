#include "HardwareAbstraction/DigitalOutputHandler.h"

DigitalOutputHandler::DigitalOutputHandler(const std::vector<int>& pins, const std::vector<std::string>& names) {
    if (pins.size() != names.size()) {
        Serial.println("Error: pins and names vectors must have the same length");
        return;
    }
    for (size_t i = 0; i < pins.size(); ++i) {
        outputs[names[i]] = DigitalOutput(pins[i]);
    }
}
void DigitalOutputHandler::SetOutput(const std::string& name, int value) {
    if (outputs.find(name) != outputs.end()) {
        outputs[name].set(value);
    } else {
        Serial.println("Error: Output not found with name: " + String(name.c_str()));
    }
}