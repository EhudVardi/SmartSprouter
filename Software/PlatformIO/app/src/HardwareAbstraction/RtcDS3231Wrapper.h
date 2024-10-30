#include <Wire.h>
#include <RTClib.h>

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

    void adjust(const DateTime& dt) {
        rtc.adjust(dt);
    }

    DateTime now() {
        return rtc.now();
    }
};
