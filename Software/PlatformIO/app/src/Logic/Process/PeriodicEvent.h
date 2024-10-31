#ifndef PERIODICEVENT_H
#define PERIODICEVENT_H

#include "Logic/Process/ActionableEvent.h"
#include "Data/DisplayTypes.h"

class PeriodicEvent : public ActionableEvent<DateTime> {
public:
    // Default constructor
    PeriodicEvent()
        : ActionableEvent<DateTime>(
            [](DateTime) { return false; },  // Default predicate always returns false
            []() {},                         // No-op start action
            []() {}),                        // No-op stop action
          interval(TimeSpan()),            // Initialize to default TimeSpan
          duration(TimeSpan()),            // Initialize to default TimeSpan
          nextStartTime(DateTime(SECONDS_FROM_1970_TO_2000)) // Initialize to epoch time
    {}
    // Constructor with parameters
    PeriodicEvent(TimeSpan p_interval, TimeSpan p_duration, std::function<void()> startAction, std::function<void()> stopAction)
        : ActionableEvent<DateTime>(
            [this](DateTime now) {
                return (now >= nextStartTime) && (now < nextStartTime + duration);
            },
            startAction, stopAction),
          interval(p_interval), duration(p_duration) {
            nextStartTime = DateTime(SECONDS_FROM_1970_TO_2000); // Start at epoch time
    }

    void update(DateTime now) {
        if (now >= nextStartTime + interval) {
            nextStartTime = now;
            this->check(now); // Check if we need to start the event
        }
    }

    void serialize(uint8_t* buffer) const override {
        ActionableEvent<DateTime>::serialize(buffer);
        buffer = serializeMember(&interval, sizeof(interval), buffer);
        buffer = serializeMember(&duration, sizeof(duration), buffer);
        buffer = serializeMember(&nextStartTime, sizeof(nextStartTime), buffer);
    }
    void deserialize(const uint8_t* buffer) override {
        ActionableEvent<DateTime>::deserialize(buffer);
        buffer = deserializeMember(&interval, sizeof(interval), buffer);
        buffer = deserializeMember(&duration, sizeof(duration), buffer);
        buffer = deserializeMember(&nextStartTime, sizeof(nextStartTime), buffer);
    }

private:
    TimeSpan interval;
    TimeSpan duration;
    DateTime nextStartTime;
};

#endif // PERIODICEVENT_H
