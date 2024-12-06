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

void ActuatorManager::SetHumidifiers(HumidifierActions action) {
    if (action == HumidifierActions::H_OFF) {
        OpenRelay1();
        return;
    }
    OpenRelay1(); delay(100);
    CloseRelay1(); delay(100);
    if (action == HumidifierActions::H_HIGH) {
        CloseRelay2(); delay(100);
        OpenRelay2(); delay(100);
    }
    else if (action == HumidifierActions::H_LOW) {
        CloseRelay2(); delay(100);
        OpenRelay2(); delay(100);
        CloseRelay2(); delay(100);
        OpenRelay2(); delay(100);
    }
}
void ActuatorManager::SetVentilators(VentilatorActions action) {
    if (action == VentilatorActions::V_BOTH_OFF) {
        OpenRelay3();
        OpenRelay4();
    }
    else if (action == VentilatorActions::V_INTAKE_ON) {
        CloseRelay3();
        OpenRelay4();
    }
    else if (action == VentilatorActions::V_EXHAUST_ON) {
        OpenRelay3();
        CloseRelay4();
    }
    else if (action == VentilatorActions::V_BOTH_ON) {
        CloseRelay3();
        CloseRelay4();
    }
}
void ActuatorManager::ShutDownAllActuators() {
    SetHumidifiers(HumidifierActions::H_OFF);
    SetVentilators(VentilatorActions::V_BOTH_OFF);
}

void ActuatorManager::CloseRelay(const std::string& name) { digitalOutputHandler->SetOutput(name, 1); }
void ActuatorManager::OpenRelay(const std::string& name) { digitalOutputHandler->SetOutput(name, 0); }