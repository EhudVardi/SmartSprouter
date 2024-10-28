#include <Wire.h>
#include <RTClib.h>

class RtcDS3231Wrapper {
private:
    RTC_DS3231 rtc; // Instance of the RTC library

public:
    // Constructor
    RtcDS3231Wrapper() {}

    // Initialize the RTC
    bool begin() {
        if (!rtc.begin()) {
            return false; // RTC not found
        }
        return true;
    }

    // Adjust the RTC time (set to specific date and time)
    void adjust(const DateTime& dt) {
        rtc.adjust(dt);
    }

    // Get the current date and time
    DateTime now() {
        return rtc.now();
    }
};
