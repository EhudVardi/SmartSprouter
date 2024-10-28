#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/RtcDS3231Wrapper.h"
#include "Data/NTPHandler.h"

class TimeManager : public BaseManager {
private:
    DateTime currentTime;           // Holds the current time
    RtcDS3231Wrapper rtcWrapper;    // Instance of RTC wrapper
    // NTPHandler ntpHandler;          // Instance of NTP handler

public:
    bool initialize() override; // Initialize the RTC and NTP handler
    void update();              // Update the current time using the RTC wrapper
    DateTime& getCurrentTime(); // Get a reference to the current time
    // bool fetchTimeFromNTP();    // Fetch the current time from NTP server and update RTC and current time
};

#endif // TIME_MANAGER_H
