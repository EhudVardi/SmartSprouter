#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/DigitalOutputHandler.h"
#include "ActuatorActions.h"

class ActuatorManager : public BaseManager {
private:
    DigitalOutputHandler* digitalOutputHandler = nullptr;

    void CloseRelay1();
    void OpenRelay1();
    
    void CloseRelay2();
    void OpenRelay2();
    
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
        } else if (action == HumidifierActions::H_LOW) {
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
