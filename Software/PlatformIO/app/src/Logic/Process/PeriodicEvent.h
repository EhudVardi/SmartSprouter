#ifndef PERIODICEVENT_H
#define PERIODICEVENT_H

#include "Logic/Process/ActionableEvent.h"
#include "Data/DisplayTypes.h"

class PeriodicEvent : public ActionableEvent<DateTime> {
public:
    PeriodicEvent(TimeSpan p_interval, TimeSpan p_duration, std::function<void()> startAction, std::function<void()> stopAction)
        : ActionableEvent<DateTime>(
            [this](DateTime now) {
                // Predicate - Check if the current time is within the active duration
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

private:
    TimeSpan interval;
    TimeSpan duration;
    DateTime nextStartTime;
};

#endif // PERIODICEVENT_H
