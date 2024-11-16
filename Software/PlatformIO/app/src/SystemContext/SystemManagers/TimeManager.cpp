#include "TimeManager.h"

// Constructor
TimeManager::TimeManager() : currentTime(nullptr) {
    currentTime = std::make_shared<AppDateTime>();
}

bool TimeManager::initialize() {
    rtcWrapper = new RtcDS3231Wrapper(RTC_SDA_PIN, RTC_SCL_PIN);
    if (!rtcWrapper->begin()) {
        return false;
    }
    update(); // Update current time instance immediately after initialization
    return true;
}

void TimeManager::update() {
    AppDateTime newTime = rtcWrapper->now(); // Fetch the current time from the RTC
    if (newTime.isValid()) {
        *currentTime = std::move(newTime); // update the manager time value if value is valid. use std:move to get ownership of the object for effectivity
    }
    else {
        // Handle RTC error
    }
}

const AppDateTime& TimeManager::getCurrentTime() const {
    return *currentTime; // Return a const reference to the current time instance
}

bool TimeManager::UpdateRtcFromNtpService(std::shared_ptr<NetworkManager> networkManager) {
    time_t fetchedEpoch;
    if (networkManager->GetTimeFromNTPService(fetchedEpoch)) {
        setTimeFromExtSource(fetchedEpoch);
        return true;
    }
    return false;
}

void TimeManager::setTimeFromExtSource(time_t& currentEpoch) {

    time_t adjustedTime = currentEpoch + UTC_OFFSET_HOURS * 3600; // Adjust UTC time offset
    *currentTime = AppDateTime(adjustedTime); // Update the current time instance
    rtcWrapper->adjust(*currentTime); // Update hardware RTC with new currentTime
}

std::string TimeManager::timeToString(time_t time) {
    char buffer[80];
    struct tm* timeInfo = gmtime(&time); // Use gmtime for UTC base
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}
