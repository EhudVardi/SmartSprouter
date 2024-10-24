#ifndef SYSTEM_CONTEXT_H
#define SYSTEM_CONTEXT_H

#include <memory>
#include "SystemContext/SystemManagers/DisplayManager.h"
#include "SystemContext/SystemManagers/InputManager.h"
#include "SystemContext/SystemManagers/SensorManager.h"
#include "SystemContext/SystemManagers/ProcessManager.h"
#include "SystemContext/SystemManagers/ActuatorManager.h"

class SystemContext {
public:
    std::shared_ptr<DisplayManager> displayManager;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<SensorManager> sensorManager;
    std::shared_ptr<ProcessManager> processManager;
    std::shared_ptr<ActuatorManager> actuatorManager;

    SystemContext();
};

#endif // SYSTEM_CONTEXT_H
