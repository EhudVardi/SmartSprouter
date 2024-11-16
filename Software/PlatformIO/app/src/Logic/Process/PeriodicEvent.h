#ifndef PERIODICEVENT_H
#define PERIODICEVENT_H

#include "ActionableEvent.h"
#include "Data/Types/AppTypes.h"

class PeriodicEvent : public ActionableEvent<AppDateTime> {
public:
    // Default constructor
    PeriodicEvent() : PeriodicEvent(AppTimeSpan(5), AppTimeSpan(1)) {}
    // Constructor with thresholds only (empty callbacks)
    PeriodicEvent(AppTimeSpan p_interval, AppTimeSpan p_duration) : ActionableEvent() {
        setTiming(p_interval, p_duration);
    }

    void setTiming(AppTimeSpan p_interval, AppTimeSpan p_duration) {
        interval = p_interval;
        duration = p_duration;
    }

    virtual void check(AppDateTime data) override {
        if (!activeSynchronized) { // one time logic - set first nextStartTime to the next interval, and set active to false
            nextStartTime = data + interval;
            active = false;
            activeSynchronized = true; // sync done
        }
        else {
            if (data >= nextStartTime) {
                if (data < nextStartTime + duration) {
                    if (!active) {
                        startAction();
                        this->active = true;
                    }
                }
                else {
                    if (active) {
                        stopAction();
                        this->active = false;
                        nextStartTime = data + interval - duration;
                    }
                }
            }
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
    bool operator!=(const PeriodicEvent& other) const {
        return !(*this == other);
    }

    String ToString() const {
        String str = "PeriodicEvent { ";
        str += "interval: " + interval.toString() + ", ";
        str += "duration: " + duration.toString() + ", ";
        str += "nextStartTime: " + nextStartTime.ToString() + ", ";
        str += ActionableEvent::ToString() + " }";
        return str;
    }

private:
    AppTimeSpan interval;
    AppTimeSpan duration;
    AppDateTime nextStartTime;
};

#endif // PERIODICEVENT_H
