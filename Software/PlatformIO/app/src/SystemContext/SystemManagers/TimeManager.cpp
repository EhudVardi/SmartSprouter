#include "SystemContext/SystemManagers/TimeManager.h"

bool TimeManager::initialize() {
    if (!rtcWrapper.begin()) {
        Serial.println("RTC initialization failed");
        return false; // Initialization failed
    }

    //ntpHandler.begin(); // Initialize NTP handler

    // Optionally adjust the RTC time once
    //rtcWrapper.adjust(DateTime(2024, 10, 27, 12, 0, 0)); // Set initial date/time
    update(); // Update current time immediately after initialization
    return true; // Successful initialization
}

void TimeManager::update() {
    currentTime = rtcWrapper.now(); // Fetch the current time from the RTC
}

DateTime& TimeManager::getCurrentTime() {
    return currentTime;
}

// bool TimeManager::fetchTimeFromNTP() {
//     time_t currentEpoch;
//     if (!ntpHandler.fetchCurrentTime(currentEpoch)) {
//         return false; // NTP fetch failed
//     }

//     // Update the current time
//     currentTime = DateTime(currentEpoch);
    
//     // Update the hardware RTC
//     rtcWrapper.adjust(currentTime);

//     return true; // Successful update
// }
