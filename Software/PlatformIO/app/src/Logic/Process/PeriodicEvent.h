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

    // Implementing serialization
    uint8_t* serialize(uint8_t* buffer) const override {
        buffer = ActionableEvent::serialize(buffer);
        buffer = serializeMember(&interval, buffer);
        buffer = serializeMember(&duration, buffer);
        return serializeMember(&nextStartTime, buffer);
    }
    const uint8_t* deserialize(const uint8_t* buffer) override {
        buffer = ActionableEvent::deserialize(buffer);
        buffer = deserializeMember(&interval, buffer);
        buffer = deserializeMember(&duration, buffer);
        return deserializeMember(&nextStartTime, buffer);
    }
    size_t getSerializedSize() const override {
        int size = ActionableEvent::getSerializedSize() + sizeof(interval) + sizeof(duration) + sizeof(nextStartTime);
        return size;
    }

    // equal operator overload
    bool operator==(const PeriodicEvent& other) const {
        return interval == other.interval &&
               duration == other.duration &&
               nextStartTime == other.nextStartTime &&
               active == other.active;
    }
    
    String ToString() const {
        String str = "PeriodicEvent { ";
        str += "interval: " + interval.toString() + ", ";
        str += "duration: " + duration.toString() + ", ";
        str += "nextStartTime: " + nextStartTime.ToArduinoString() + ", ";
        str += ActionableEvent::ToString() + " }";
        return str;
    }

private:
    DisplayTimeSpan interval;
    DisplayTimeSpan duration;
    DisplayDateTime nextStartTime;
};

#endif // PERIODICEVENT_H
