#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/RtcDS3231Wrapper.h"
#include "Data/NTPHandler.h"

class TimeManager : public BaseManager {
private:
    DateTime currentTime;           // Holds the current time
    RtcDS3231Wrapper rtcWrapper;    // Instance of RTC wrapper

    int utcOffsetHours = 2; // utc offset

public:
    bool initialize() override; // Initialize the RTC and NTP handler
    void update();  // Update the current time using the RTC wrapper
    DateTime& getCurrentTime(); // Get a reference to the current time
    void setTimeFromExtSource(time_t& currentEpoch); // set time retrieved from external source
    std::string timeToString(time_t time); // Function to format time as a human-readable string
};

#endif // TIME_MANAGER_H
