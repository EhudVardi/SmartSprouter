#include "ActuatorManager.h"

bool ActuatorManager::initialize() {

    std::vector<int> digitalOutputPins = { 
        DIGITAL_OUTPUT_RELAY1_PIN, 
        DIGITAL_OUTPUT_RELAY2_PIN, 
        DIGITAL_OUTPUT_RELAY3_PIN, 
        DIGITAL_OUTPUT_RELAY4_PIN, 
        DIGITAL_OUTPUT_RELAY5_PIN, 
        DIGITAL_OUTPUT_RELAY6_PIN 
    };
    std::vector<std::string> digitalOutputNames = { 
        DIGITAL_OUTPUT_RELAY1_NAME, 
        DIGITAL_OUTPUT_RELAY2_NAME, 
        DIGITAL_OUTPUT_RELAY3_NAME, 
        DIGITAL_OUTPUT_RELAY4_NAME, 
        DIGITAL_OUTPUT_RELAY5_NAME, 
        DIGITAL_OUTPUT_RELAY6_NAME 
    };

    digitalOutputHandler = new DigitalOutputHandler(digitalOutputPins, digitalOutputNames);

    return true;
}

void ActuatorManager::CloseRelay(const std::string& name) { digitalOutputHandler->SetOutput(name, 1); }
void ActuatorManager::OpenRelay(const std::string& name) { digitalOutputHandler->SetOutput(name, 0); }