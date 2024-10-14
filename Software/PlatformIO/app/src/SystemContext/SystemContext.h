#ifndef SYSTEM_CONTEXT_H
#define SYSTEM_CONTEXT_H

#include <memory>
#include "DisplayManager.h"
#include "InputManager.h"
#include "SensorManager.h"
#include "ProcessManager.h"
#include "ActuatorManager.h"

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
