#include "SystemContext.h"

SystemContext::SystemContext() {
    displayManager = std::make_shared<DisplayManager>();
    inputManager = std::make_shared<InputManager>();
    sensorManager = std::make_shared<SensorManager>();
    processManager = std::make_shared<ProcessManager>();
    actuatorManager = std::make_shared<ActuatorManager>();
    timeManager = std::make_shared<TimeManager>();
    networkManager = std::make_shared<NetworkManager>();
}
