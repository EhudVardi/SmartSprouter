#include "Application.h"

void Application::setup() {

    // Initialize managers in context
    context.displayManager = std::make_shared<DisplayManager>();
    context.sensorManager = std::make_shared<SensorManager>();
    context.processManager = std::make_shared<ProcessManager>();
    context.actuatorManager = std::make_shared<ActuatorManager>();
    context.timeManager = std::make_shared<TimeManager>();
    context.networkManager = std::make_shared<NetworkManager>();
    context.inputManager = std::make_shared<InputManager>();
    context.inputManager->registerEventHandler(InputEvent::BackPressed, [this]() {
        stateMachine.handleInput(InputEvent::BackPressed, &context);
    });
    context.inputManager->registerEventHandler(InputEvent::BackReleased, [this]() {
        stateMachine.handleInput(InputEvent::BackReleased, &context);
    });
    context.inputManager->registerEventHandler(InputEvent::RotatedLeft, [this]() {
        stateMachine.handleInput(InputEvent::RotatedLeft, &context);
    });
    context.inputManager->registerEventHandler(InputEvent::RotatedRight, [this]() {
        stateMachine.handleInput(InputEvent::RotatedRight, &context);
    });
    context.inputManager->registerEventHandler(InputEvent::EnterPressed, [this]() {
        stateMachine.handleInput(InputEvent::EnterPressed, &context);
    });
    context.inputManager->registerEventHandler(InputEvent::EnterReleased, [this]() {
        stateMachine.handleInput(InputEvent::EnterReleased, &context);
    });

    // Initialize state machine to initial state
    stateMachine.changeState(AppStates::STARTING_UP, &context);

    // Setup polling timers
    inputPollingTimer.setInterval(1);
    inputPollingTimer.setCallback([&]() {
        context.inputManager->pollInputs();
    });

    stateMachineTimer.setInterval(200);
    stateMachineTimer.setCallback([&]() {
        stateMachine.update(&context);
    });

    timePollingTimer.setInterval(500);
    timePollingTimer.setCallback([&]() {
        context.timeManager->update();
    });

    inputPollingTimer.start();
    stateMachineTimer.start();
    timePollingTimer.start();
}

void Application::loop() {

    // update all polling timers
    inputPollingTimer.update();
    stateMachineTimer.update();
    timePollingTimer.update();
}
