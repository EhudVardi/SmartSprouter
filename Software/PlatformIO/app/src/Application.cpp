#include "Application.h"

#include "StateMachine/States/StartingUpState.h"
#include "StateMachine/States/SystemInErrorState.h"
#include "StateMachine/States/InitializingState.h"
#include "StateMachine/States/IdlingState.h"
#include "StateMachine/States/InformingState.h"
#include "StateMachine/States/SettingProcessState.h"
#include "StateMachine/States/SettingParamState.h"
#include "StateMachine/States/RunningState.h"
#include "StateMachine/States/AbortingState.h"

#include <iostream>
#include <cmath>  // for std::isnan
#include <string> // for std::to_string

void Application::setup() {
    // Initialize managers in context
    context.displayManager = std::make_shared<DisplayManager>();
    context.inputManager = std::make_shared<InputManager>();
    context.sensorManager = std::make_shared<SensorManager>();
    context.processManager = std::make_shared<ProcessManager>();
    context.actuatorManager = std::make_shared<ActuatorManager>();

    context.inputManager->initialize();

    context.inputManager->registerEventHandler(InputEvent::BackPressed, [this]() {
        //stateMachine.handleInput(InputEvent::BackPressed, &context);
        std::cout << "BackPressed" << std::endl ;
    });
    context.inputManager->registerEventHandler(InputEvent::BackReleased, [this]() {
        //stateMachine.handleInput(InputEvent::BackReleased, &context);
        std::cout << "BackReleased" << std::endl ;
    });
    context.inputManager->registerEventHandler(InputEvent::RotatedLeft, [this]() {
        //stateMachine.handleInput(InputEvent::RotatedLeft, &context);
        std::cout << "RotatedLeft" << std::endl ;
    });
    context.inputManager->registerEventHandler(InputEvent::RotatedRight, [this]() {
        //stateMachine.handleInput(InputEvent::RotatedRight, &context);
        std::cout << "RotatedRight" << std::endl ;
    });
    context.inputManager->registerEventHandler(InputEvent::EnterPressed, [this]() {
        //stateMachine.handleInput(InputEvent::EnterPressed, &context);
        std::cout << "EnterPressed" << std::endl ;
    });
    context.inputManager->registerEventHandler(InputEvent::EnterReleased, [this]() {
        //stateMachine.handleInput(InputEvent::EnterReleased, &context);
        std::cout << "EnterReleased" << std::endl ;
    });
    

    context.sensorManager->initialize();



    context.actuatorManager->initialize();



    // Set initial state
    auto runningState = std::make_shared<RunningState>();
    stateMachine.changeState(runningState, &context);
}

void Application::loop() {
    // Poll input and sensor managers
    context.inputManager->pollInputs();

    // float temperature = context.sensorManager->getTemperature();
    // std::cout << "temperature = " << (!std::isnan(temperature) ? std::to_string(temperature) : "nan") << std::endl;
    // float humidity = context.sensorManager->getHumidity();
    // std::cout << "humidity = " << (!std::isnan(humidity) ? std::to_string(humidity) : "nan") << std::endl;
    

    context.actuatorManager->CloseRelay1();
    context.actuatorManager->OpenRelay2();

    delay(500);
    
    context.actuatorManager->CloseRelay2();
    context.actuatorManager->OpenRelay1();

    delay(500);
    
    // Update state machine
    stateMachine.update(&context);

}

