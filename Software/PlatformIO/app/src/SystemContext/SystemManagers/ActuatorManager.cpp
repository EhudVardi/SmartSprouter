#include "SystemContext/SystemManagers/ActuatorManager.h"
#include "SystemContext/HWSystemPins/ActuatorPins.h"
#include <iostream>

bool ActuatorManager::initialize() {

    std::vector<int> digitalOutputPins = { DIGITAL_OUTPUT_RELAY1_PIN, DIGITAL_OUTPUT_RELAY2_PIN };
    std::vector<std::string> digitalOutputNames = { DIGITAL_OUTPUT_RELAY1_NAME, DIGITAL_OUTPUT_RELAY2_NAME };

    digitalOutputHandler = new DigitalOutputHandler(digitalOutputPins, digitalOutputNames);

    return true;
}

void ActuatorManager::CloseRelay1() { digitalOutputHandler->SetOutput(DIGITAL_OUTPUT_RELAY1_NAME, 1); }
void ActuatorManager::OpenRelay1()  { digitalOutputHandler->SetOutput(DIGITAL_OUTPUT_RELAY1_NAME, 0); }
void ActuatorManager::CloseRelay2() { digitalOutputHandler->SetOutput(DIGITAL_OUTPUT_RELAY2_NAME, 1); }
void ActuatorManager::OpenRelay2()  { digitalOutputHandler->SetOutput(DIGITAL_OUTPUT_RELAY2_NAME, 0); }
