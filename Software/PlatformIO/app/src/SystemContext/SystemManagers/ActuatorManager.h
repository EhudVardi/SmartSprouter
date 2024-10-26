#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include "BaseManager.h"

#include "HardwareAbstraction/DigitalOutputHandler.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"

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
        if (action == HumidifierActions::Off) {
            OpenRelay1();
            return;
        }
        OpenRelay1();
        delay(100);
        CloseRelay1();
        delay(100);
        if (action == HumidifierActions::High) {
            CloseRelay2();
            delay(100);
            OpenRelay2();
            delay(100);
        } else if (action == HumidifierActions::Low) {
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
};

#endif // ACTUATOR_MANAGER_H
