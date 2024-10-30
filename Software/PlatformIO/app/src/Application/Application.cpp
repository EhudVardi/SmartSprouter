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

    inputPollingTimer.update();
    stateMachineTimer.update();
    timePollingTimer.update();
}



//////Data store serialization and NOVRAM

// #include "Data/Process.h"
// #include "Data/PreferenceHandler.h"


    // PreferenceHandler prefHandler("AppProcess");

    // Process process(10, 30, 20, 25, DisplayTimeSpan(1,2,3,4));
    // prefHandler.saveObjectToNVS(process, "CurrProcess");

    // log("Object created and saved");
    // log(process.toString().c_str());

    // process.TickDurationDown();
    
    // prefHandler.saveObjectToNVS(process, "CurrProcess");
    // log("Object modified and saved");
    // log(process.toString().c_str());

    // Process loadedProcess;

    // if (prefHandler.loadObjectFromNVS(loadedProcess, "CurrProcess")) {
    //     log("Object loaded successfully:");
    //     log(loadedProcess.toString().c_str());
    // } else {
    //     log("Object not found or corrupted.");
    // }

    // if (prefHandler.clearObjectFromNVS("CurrProcess")) {
    //     log("Object cleared successfully:");
    // } else {
    //     log("Object failed to clear:");
    // }


    // while(true) {delay(1000);}


