#include <Arduino.h>
#include <functional>

class Timer {
private:
    unsigned long interval;
    unsigned long lastUpdate;
    std::function<void()> callback;
    bool active;

public:
    Timer() : interval(1000), lastUpdate(0), active(false) {}
    Timer(unsigned long pollInterval) : Timer() { interval = pollInterval; }
    Timer(unsigned long pollInterval, std::function<void()> callbackFunc) : Timer(interval) { callback = callbackFunc; }

    void update() {
        unsigned long currentMillis = millis();
        if (currentMillis - lastUpdate >= interval) {
            callback();  // Call the registered callback function
            lastUpdate += interval;  // Add interval to lastUpdate to maintain accuracy
        }
    }

    void setCallback(std::function<void()> callbackFunc) {
        callback = callbackFunc;
    }
    void setInterval(unsigned long newInterval) {
        interval = newInterval;
    }

    void start() {
        active = true;
        lastUpdate = millis();
    }
    void stop() {
        active = false;
    }
    void reset() {
        lastUpdate = millis();
    }
};
