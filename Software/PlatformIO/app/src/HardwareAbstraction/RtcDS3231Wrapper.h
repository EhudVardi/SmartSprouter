#include <Wire.h>
#include <RTClib.h>
#include "Data/DisplayTypes.h"

class RtcDS3231Wrapper {
private:
    TwoWire i2cwires = TwoWire(1);  //I2C bus #1
    RTC_DS3231 rtc;

public:
    RtcDS3231Wrapper(int sda_pin, int scl_pin) {
        i2cwires.begin(sda_pin, scl_pin);
    }

    bool begin() {
        if (!rtc.begin(&i2cwires)) {
            return false;
        }
        return true;
    }

    void adjust(const DisplayDateTime& dt) {
        rtc.adjust(dt);
        //rtc.adjust(static_cast<const DateTime&>(dt));
    }

    DateTime now() {
        return DisplayDateTime(rtc.now());
    }
};
