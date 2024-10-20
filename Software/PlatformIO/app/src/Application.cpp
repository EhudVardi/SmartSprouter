#include "Application.h"

void Application::setup() {
    // Initialize managers in context
    context.displayManager = std::make_shared<DisplayManager>();
    context.sensorManager = std::make_shared<SensorManager>();
    context.processManager = std::make_shared<ProcessManager>();
    context.actuatorManager = std::make_shared<ActuatorManager>();
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

    stateMachine.changeState("StartingUpState", &context);
}

void Application::loop() {
    // Poll input and sensor managers
    //context.inputManager->pollInputs();

    /// test dht11 sensor
    // float temperature = context.sensorManager->getTemperature();
    // std::cout << "temperature = " << (!std::isnan(temperature) ? std::to_string(temperature) : "nan") << std::endl;
    // float humidity = context.sensorManager->getHumidity();
    // std::cout << "humidity = " << (!std::isnan(humidity) ? std::to_string(humidity) : "nan") << std::endl;
    
    /// test actuator - relays
    // context.actuatorManager->CloseRelay1();
    // context.actuatorManager->OpenRelay2();
    // delay(500);
    // context.actuatorManager->CloseRelay2();
    // context.actuatorManager->OpenRelay1();
    // delay(500);

    //context.displayManager->refresh();
    //delay(500);
    
    // Update state machine
    stateMachine.update(&context);
    delay(500);

}

