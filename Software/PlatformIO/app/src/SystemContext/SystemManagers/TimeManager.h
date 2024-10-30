#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "BaseManager.h"
#include "HardwareAbstraction/RtcDS3231Wrapper.h"
#include "Data/NTPHandler.h"
#include "SystemContext/SystemManagers/NetworkManager.h"
#include "Data/DisplayTypes.h"

class TimeManager : public BaseManager {
private:
    std::shared_ptr<DisplayDateTime> currentTime; // Smart pointer to hold the current time
    RtcDS3231Wrapper* rtcWrapper = nullptr; // Instance of RTC wrapper

public:
    TimeManager(); // Constructor

    bool initialize() override; // Initialize the RTC and NTP handler
    void update();  // Update the current time using the RTC wrapper
    const DisplayDateTime& getCurrentTime() const; // Get a constant reference to the current time
    bool UpdateRtcFromNtpService(NetworkManager* networkManager);
    void setTimeFromExtSource(time_t& currentEpoch); // Set time retrieved from an external source
    std::string timeToString(time_t time); // Function to format time as a human-readable string
};

#endif // TIME_MANAGER_H
