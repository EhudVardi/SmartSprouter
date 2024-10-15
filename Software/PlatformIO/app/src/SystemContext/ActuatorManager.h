#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include "BaseManager.h"

#include "HardwareAbstraction/DigitalOutputHandler.h"

class ActuatorManager : public BaseManager {
private:
    DigitalOutputHandler* digitalOutputHandler = nullptr;
    
public:
    bool initialize() override;

    void CloseRelay1();
    void OpenRelay1();
    
    void CloseRelay2();
    void OpenRelay2();
};

#endif // ACTUATOR_MANAGER_H
