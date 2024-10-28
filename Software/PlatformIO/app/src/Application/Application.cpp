#include "Application/Application.h"

void Application::setup() {

    // Initialize managers in context
    context.displayManager = std::make_shared<DisplayManager>();
    context.sensorManager = std::make_shared<SensorManager>();
    context.processManager = std::make_shared<ProcessManager>();
    context.actuatorManager = std::make_shared<ActuatorManager>();
    context.timeManager = std::make_shared<TimeManager>();
    context.inputManager = std::make_shared<InputManager>();
    context.networkManager = std::make_shared<NetworkManager>();

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


    stateMachine.changeState(AppStates::StartingUp, &context);


    inputPollingTimer.setInterval(1);
    inputPollingTimer.setCallback([&]() {
        context.inputManager->pollInputs();
    });

    stateMachineTimer.setInterval(500);
    stateMachineTimer.setCallback([&]() {
        stateMachine.update(&context);
    });

    inputPollingTimer.start();
    stateMachineTimer.start();
}

void Application::loop() {

    inputPollingTimer.update();
    stateMachineTimer.update();
    
}



//////Data store serialization and NOVRAM

// #include "Data/Process.h"
// #include "Data/PreferenceHandler.h"
// #include <iostream>


    // PreferenceHandler prefHandler("AppProcess");

    // Process process(10, 30, 20, 25, DisplayDuration(1,2,3,4));
    // prefHandler.saveObjectToNVS(process, "CurrProcess");

    // std::cout << "Object created and saved" << std::endl;
    // std::cout << process.toString().c_str() << std::endl;

    // process.TickDurationDown();
    
    // prefHandler.saveObjectToNVS(process, "CurrProcess");
    // std::cout << "Object modified and saved" << std::endl;
    // std::cout << process.toString().c_str() << std::endl;

    // Process loadedProcess;

    // if (prefHandler.loadObjectFromNVS(loadedProcess, "CurrProcess")) {
    //     std::cout << "Object loaded successfully:" << std::endl;
    //     std::cout << loadedProcess.toString().c_str() << std::endl;
    // } else {
    //     std::cout << "Object not found or corrupted." << std::endl;
    // }

    // if (prefHandler.clearObjectFromNVS("CurrProcess")) {
    //     std::cout << "Object cleared successfully:" << std::endl;
    // } else {
    //     std::cout << "Object failed to clear:" << std::endl;
    // }


    // while(true) {delay(1000);}


