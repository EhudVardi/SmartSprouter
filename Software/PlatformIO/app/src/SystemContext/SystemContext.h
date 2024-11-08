#ifndef SYSTEM_CONTEXT_H
#define SYSTEM_CONTEXT_H

#include <memory>
#include "SystemManagers/DisplayManager.h"
#include "SystemManagers/InputManager.h"
#include "SystemManagers/SensorManager.h"
#include "SystemManagers/ProcessManager.h"
#include "SystemManagers/ActuatorManager.h"
#include "SystemManagers/TimeManager.h"
#include "SystemManagers/NetworkManager.h"

class SystemContext {
public:
    std::shared_ptr<DisplayManager> displayManager;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<SensorManager> sensorManager;
    std::shared_ptr<ProcessManager> processManager;
    std::shared_ptr<ActuatorManager> actuatorManager;
    std::shared_ptr<TimeManager> timeManager;
    std::shared_ptr<NetworkManager> networkManager;

    SystemContext();
};

#endif // SYSTEM_CONTEXT_H
