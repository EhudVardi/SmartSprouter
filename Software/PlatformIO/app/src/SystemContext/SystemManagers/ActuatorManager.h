#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/DigitalOutputHandler.h"
#include "ActuatorActions.h"

class ActuatorManager : public BaseManager {
private:
    DigitalOutputHandler* digitalOutputHandler = nullptr;
    
    void CloseRelay(const std::string& name);
    void OpenRelay(const std::string& name);
    
    inline void CloseRelay1() { CloseRelay(DIGITAL_OUTPUT_RELAY1_NAME); }
    inline void CloseRelay2() { CloseRelay(DIGITAL_OUTPUT_RELAY2_NAME); }
    inline void CloseRelay3() { CloseRelay(DIGITAL_OUTPUT_RELAY3_NAME); }
    inline void CloseRelay4() { CloseRelay(DIGITAL_OUTPUT_RELAY4_NAME); }
    inline void CloseRelay5() { CloseRelay(DIGITAL_OUTPUT_RELAY5_NAME); }
    inline void CloseRelay6() { CloseRelay(DIGITAL_OUTPUT_RELAY6_NAME); }
    inline void OpenRelay1() { OpenRelay(DIGITAL_OUTPUT_RELAY1_NAME); }
    inline void OpenRelay2() { OpenRelay(DIGITAL_OUTPUT_RELAY2_NAME); }
    inline void OpenRelay3() { OpenRelay(DIGITAL_OUTPUT_RELAY3_NAME); }
    inline void OpenRelay4() { OpenRelay(DIGITAL_OUTPUT_RELAY4_NAME); }
    inline void OpenRelay5() { OpenRelay(DIGITAL_OUTPUT_RELAY5_NAME); }
    inline void OpenRelay6() { OpenRelay(DIGITAL_OUTPUT_RELAY6_NAME); }

public:
    bool initialize() override;

    void SetHumidifiers(HumidifierActions action) {
        if (action == HumidifierActions::H_OFF) {
            OpenRelay1();
            return;
        }
        OpenRelay1();
        delay(100);
        CloseRelay1();
        delay(100);
        if (action == HumidifierActions::H_HIGH) {
            CloseRelay2();
            delay(100);
            OpenRelay2();
            delay(100);
        }
        else if (action == HumidifierActions::H_LOW) {
            CloseRelay2();
            delay(100);
            OpenRelay2();
            delay(100);
            CloseRelay2();
            delay(100);
            OpenRelay2();
            delay(100);
        }
    }

    void ShutDownAllActuators() {
        SetHumidifiers(HumidifierActions::H_OFF);
    }
};

#endif // ACTUATOR_MANAGER_H
