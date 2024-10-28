#include "SystemContext/SystemManagers/TimeManager.h"

// Constructor
TimeManager::TimeManager() : currentTime(nullptr) {
    currentTime = new DateTime(); // Initialize currentTime with a new DateTime instance
}

// Destructor
TimeManager::~TimeManager() {
    delete currentTime; // Free the allocated memory
}

bool TimeManager::initialize() {
    rtcWrapper = new RtcDS3231Wrapper(RTC_SDA_PIN, RTC_SCL_PIN);
    if (!rtcWrapper->begin()) {
        return false; // Initialization failed
    }
    update(); // Update current time instance immediately after initialization
    return true; // Successful initialization
}

void TimeManager::update() {
    *currentTime = rtcWrapper->now(); // Fetch the current time from the RTC and update the value
}

DateTime& TimeManager::getCurrentTime() {
    return *currentTime; // Return a reference to the current time instance
}

void TimeManager::setTimeFromExtSource(time_t& currentEpoch) {
    // Adjust UTC time offset
    time_t adjustedTime = currentEpoch + utcOffsetHours * 3600;
    // Update the current time instance
    *currentTime = DateTime(adjustedTime);
    // Update hardware RTC with the new time
    rtcWrapper->adjust(*currentTime); // Pass currentTime to adjust
}

std::string TimeManager::timeToString(time_t time) {
    char buffer[80];
    struct tm* timeInfo = gmtime(&time); // Use gmtime for UTC base
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}
