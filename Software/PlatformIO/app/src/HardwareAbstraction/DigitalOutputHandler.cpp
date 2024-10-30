#include "HardwareAbstraction/DigitalOutputHandler.h"

DigitalOutputHandler::DigitalOutputHandler(const std::vector<int>& pins, const std::vector<std::string>& names) {
    if (pins.size() != names.size()) {
        log("Error: pins and names vectors must have the same length");
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
        log("Error: Output not found with name: " + name);
    }
}