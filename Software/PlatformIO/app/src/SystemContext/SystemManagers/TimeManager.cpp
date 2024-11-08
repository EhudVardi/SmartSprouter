#include "SystemContext/SystemManagers/TimeManager.h"
#include "Data/AppTypes.h"

// Constructor
TimeManager::TimeManager() : currentTime(nullptr) {
    currentTime = std::make_shared<AppDateTime>();
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
    AppDateTime newTime = rtcWrapper->now(); // Fetch the current time from the RTC
    if (newTime.isValid()) {
        *currentTime = std::move(newTime); // update the manager time value if value is valid. use std:move to get ownership of the object for effectivity
    } else {
        // Handle RTC error
    }
}

const AppDateTime& TimeManager::getCurrentTime() const {
    return *currentTime; // Return a const reference to the current time instance
}

bool TimeManager::UpdateRtcFromNtpService(std::shared_ptr<NetworkManager> networkManager) {
    time_t fetchedEpoch;
    if (networkManager->GetTimeFromNTPService(fetchedEpoch)){
        setTimeFromExtSource(fetchedEpoch);
        return true;
    }
    return false;
}

void TimeManager::setTimeFromExtSource(time_t& currentEpoch) {
    // Adjust UTC time offset
    time_t adjustedTime = currentEpoch + utcOffsetHours * 3600;
    // Update the current time instance
    *currentTime = AppDateTime(adjustedTime);
    // Update hardware RTC with the new time
    rtcWrapper->adjust(*currentTime); // Pass currentTime to adjust
}

std::string TimeManager::timeToString(time_t time) {
    char buffer[80];
    struct tm* timeInfo = gmtime(&time); // Use gmtime for UTC base
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}
