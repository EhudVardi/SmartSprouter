#include "Application.h"
#include "RunningState.h"

void Application::setup() {
    // Initialize managers in context
    context.displayManager = std::make_shared<DisplayManager>();
    context.inputManager = std::make_shared<InputManager>();
    context.sensorManager = std::make_shared<SensorManager>();
    context.processManager = std::make_shared<ProcessManager>();

    // Register event handlers for input events
    context.inputManager->registerEventHandler(InputEvent::ButtonXPressed, [this]() {
        stateMachine.handleInput(InputEvent::ButtonXPressed, &context);
    });

    // Set initial state
    auto runningState = std::make_shared<RunningState>();
    stateMachine.changeState(runningState, &context);
}

void Application::loop() {
    // Poll input and sensor managers
    context.inputManager->pollInputs();
    context.sensorManager->readSensors();

    // Update state machine
    stateMachine.update(&context);
}
