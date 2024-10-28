#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/RtcDS3231Wrapper.h"
#include "Data/NTPHandler.h"

class TimeManager : public BaseManager {
private:
    DateTime* currentTime; // Pointer to hold the current time
    RtcDS3231Wrapper* rtcWrapper = nullptr; // Instance of RTC wrapper

public:
    TimeManager(); // Constructor
    ~TimeManager(); // Destructor

    bool initialize() override; // Initialize the RTC and NTP handler
    void update();  // Update the current time using the RTC wrapper
    const DateTime& getCurrentTime() const; // Get a constant reference to the current time
    void setTimeFromExtSource(time_t& currentEpoch); // Set time retrieved from an external source
    std::string timeToString(time_t time); // Function to format time as a human-readable string
};

#endif // TIME_MANAGER_H
