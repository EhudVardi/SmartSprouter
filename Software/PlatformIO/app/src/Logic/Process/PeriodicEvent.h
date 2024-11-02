#ifndef PERIODICEVENT_H
#define PERIODICEVENT_H

#include "Logic/Process/ActionableEvent.h"
#include "Data/DisplayTypes.h"

class PeriodicEvent : public ActionableEvent<DisplayDateTime> {
public:
    // Default constructor
    PeriodicEvent()
        : ActionableEvent<DisplayDateTime>(
            [](DisplayDateTime) { return false; },  // Default predicate always returns false
            []() {},                         // No-op start action
            []() {}),                        // No-op stop action
          interval(DisplayTimeSpan()),            // Initialize to default DisplayTimeSpan
          duration(DisplayTimeSpan()),            // Initialize to default DisplayTimeSpan
          nextStartTime(DisplayDateTime(SECONDS_FROM_1970_TO_2000)) // Initialize to epoch time
    {}
    // Constructor with parameters
    PeriodicEvent(DisplayTimeSpan p_interval, DisplayTimeSpan p_duration, std::function<void()> startAction, std::function<void()> stopAction)
        : ActionableEvent<DisplayDateTime>(
            [this](DisplayDateTime now) {
                return (now >= nextStartTime) && (now < nextStartTime + duration);
            },
            startAction, stopAction),
          interval(p_interval), duration(p_duration) {
            nextStartTime = DisplayDateTime(SECONDS_FROM_1970_TO_2000); // Start at epoch time
    }

    void update(DisplayDateTime now) {
        if (now >= nextStartTime + interval) {
            nextStartTime = now;
            this->check(now); // Check if we need to start the event
        }
    }

    void serialize(uint8_t* buffer) const override {
        ActionableEvent<DisplayDateTime>::serialize(buffer);
        buffer = serializeMember(&interval, sizeof(interval), buffer);
        buffer = serializeMember(&duration, sizeof(duration), buffer);
        buffer = serializeMember(&nextStartTime, sizeof(nextStartTime), buffer);

    // equal operator overload
    bool operator==(const PeriodicEvent& other) const {
        return interval == other.interval &&
               duration == other.duration &&
               nextStartTime == other.nextStartTime &&
               active == other.active;
    }
    void deserialize(const uint8_t* buffer) override {
        ActionableEvent<DisplayDateTime>::deserialize(buffer);
        buffer = deserializeMember(&interval, sizeof(interval), buffer);
        buffer = deserializeMember(&duration, sizeof(duration), buffer);
        buffer = deserializeMember(&nextStartTime, sizeof(nextStartTime), buffer);
    
    String ToString() const {
        String str = "PeriodicEvent { ";
        str += "interval: " + interval.toString() + ", ";
        str += "duration: " + duration.toString() + ", ";
        str += "nextStartTime: " + nextStartTime.ToArduinoString() + ", ";
        str += "active: " + String(active ? "true" : "false") + " }";
        return str;
    }

private:
    DisplayTimeSpan interval;
    DisplayTimeSpan duration;
    DisplayDateTime nextStartTime;
};

#endif // PERIODICEVENT_H
