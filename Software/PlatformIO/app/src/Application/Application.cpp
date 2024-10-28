#include "Application/Application.h"



#include <iostream>
#include <ctime>
#include "Data/WiFiHandler.h"
#include "Data/NTPHandler.h"

// Function to adjust for UTC offset
time_t adjustUTC(time_t epochTime, int utcOffsetHours) {
    return epochTime + utcOffsetHours * 3600;
}

// Function to format time as a human-readable string
std::string formatTime(time_t epochTime) {
    char buffer[80];
    struct tm* timeInfo = gmtime(&epochTime); // Use gmtime for UTC base
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}




void Application::setup() {


    // Instantiate WiFi and NTP handlers
    WiFiHandler wifiHandler;
    NTPHandler ntpHandler("pool.ntp.org", wifiHandler);

    const char* ssid = "SSID"; // Your Wi-Fi SSID
    const char* password = "password"; // Your Wi-Fi password

    // Connect to WiFi (replace with your network credentials)
    if (wifiHandler.connect(ssid, password)) {
        // Begin the NTP connection
        ntpHandler.begin(wifiHandler);

        // Define a UTC offset (e.g., UTC+2 for Central European Time)
        int utcOffsetHours = 2;

        while(true) {


            // Fetch the current time from the NTP server
            time_t currentEpoch;
            if (ntpHandler.fetchCurrentTime(currentEpoch, wifiHandler)) {
                // Adjust the fetched time for the UTC offset
                time_t adjustedTime = adjustUTC(currentEpoch, utcOffsetHours);

                // Format and print the adjusted time
                std::cout << "Current Time (UTC+" << utcOffsetHours << "): " << formatTime(adjustedTime) << std::endl;
            } else {
                std::cout << "Failed to fetch time from NTP server." << std::endl;
            }


            delay(5000);

        }

        // Disconnect WiFi
        wifiHandler.disconnect();
    } else {
        std::cout << "Failed to connect to WiFi." << std::endl;
    }
    while(true) {  delay(5000); }




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








//////NTP example

//#include <iostream>
// #include <ctime>
// #include "Data/WiFiHandler.h"
// #include "Data/NTPHandler.h"

// // Function to adjust for UTC offset
// time_t adjustUTC(time_t epochTime, int utcOffsetHours) {
//     return epochTime + utcOffsetHours * 3600;
// }

// // Function to format time as a human-readable string
// std::string formatTime(time_t epochTime) {
//     char buffer[80];
//     struct tm* timeInfo = gmtime(&epochTime); // Use gmtime for UTC base
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
//     return std::string(buffer);
// }

    // // Instantiate WiFi and NTP handlers
    // WiFiHandler wifiHandler;
    // NTPHandler ntpHandler("pool.ntp.org", wifiHandler);

    // const char* ssid = "EVFU"; // Your Wi-Fi SSID
    // const char* password = "ApSoDiFu01928374"; // Your Wi-Fi password

    // // Connect to WiFi (replace with your network credentials)
    // if (wifiHandler.connect(ssid, password)) {
    //     // Begin the NTP connection
    //     ntpHandler.begin(wifiHandler);

    //     // Define a UTC offset (e.g., UTC+2 for Central European Time)
    //     int utcOffsetHours = 2;

    //     while(true) {


    //         // Fetch the current time from the NTP server
    //         time_t currentEpoch;
    //         if (ntpHandler.fetchCurrentTime(currentEpoch, wifiHandler)) {
    //             // Adjust the fetched time for the UTC offset
    //             time_t adjustedTime = adjustUTC(currentEpoch, utcOffsetHours);

    //             // Format and print the adjusted time
    //             std::cout << "Current Time (UTC+" << utcOffsetHours << "): " << formatTime(adjustedTime) << std::endl;
    //         } else {
    //             std::cout << "Failed to fetch time from NTP server." << std::endl;
    //         }


    //         delay(5000);

    //     }

    //     // Disconnect WiFi
    //     wifiHandler.disconnect();
    // } else {
    //     std::cout << "Failed to connect to WiFi." << std::endl;
    // }
    // while(true) {  delay(5000); }