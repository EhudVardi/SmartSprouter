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

// #include "Data/PreferenceHandler.h"
// #include "Logic/Process/Process.h"


    // PreferenceHandler prefHandler("AppProcess");

    // prefHandler.clearObjectFromNVS("CurrProcess");
    
    // // Initialize a Process object
    // Process process;

    // // Initialize a PeriodicEvent (for example, every 10 minutes with 1 minute duration)
    // PeriodicEvent periodicEvent(
    //     DisplayTimeSpan(1,2,3,4),               // Interval
    //     DisplayTimeSpan(5,6,7,8),                // Duration
    //     []() { log("PeriodicEvent Start\n"); },  // Start Action
    //     []() { log("PeriodicEvent Stop\n"); }    // Stop Action
    // );

    // // Initialize a WindowEvent with thresholds
    // WindowEvent windowEvent(
    //     30.0f,                                   // Low threshold
    //     70.0f,                                   // High threshold
    //     []() { log("WindowEvent Start\n"); },    // Start Action
    //     []() { log("WindowEvent Stop\n"); }      // Stop Action
    // );
    
    // process.addPeriodicEvent(periodicEvent);
    // process.addSensorEvent(windowEvent);

    // // init some empty events
    // WindowEvent windowEvent2;
    // process.addSensorEvent(windowEvent2);
    // WindowEvent windowEvent3;
    // process.addSensorEvent(windowEvent3);
    
    // PeriodicEvent periodicEvent2;
    // process.addPeriodicEvent(periodicEvent2);
    // PeriodicEvent periodicEvent3;
    // process.addPeriodicEvent(periodicEvent3);

    // log("saving to NOV.");
    // prefHandler.saveObjectToNVS(process, "CurrProcess");
    
    // log("loading from NOV");
    // Process loadedProcess;
    // if (prefHandler.loadObjectFromNVS(loadedProcess, "CurrProcess")) {
    //     log("Object loaded successfully:");
    // } else {
    //     log("Object not found or corrupted.");
    // }

    // log("comparing instances");
    // if (process == loadedProcess) {
    //     log("instances equal!");
    // } else {
    //     log("instances different..");
    // }

    // if (prefHandler.clearObjectFromNVS("CurrProcess")) {
    //     log("Object cleared successfully:");
    // } else {
    //     log("Object failed to clear:");
    // }

    // log("finished");
    // while(true) {delay(1000);}