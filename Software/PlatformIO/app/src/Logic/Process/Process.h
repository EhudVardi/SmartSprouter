#ifndef PROCESS_H
#define PROCESS_H

#include "Logic/Process/PeriodicEvent.h"
#include "Logic/Process/WindowEvent.h"
#include "Data/ISerializable.h"
#include <list>

class Process : public ISerializable {
public:
    void addPeriodicEvent(const PeriodicEvent& event) {
        periodicEvents.push_back(event);
    }
    void addSensorEvent(const WindowEvent& event) {
        windowEvents.push_back(event);
    }

    void updatePeriodicEvents(DateTime currentTime) {
        for (auto& event : periodicEvents) {
            event.update(currentTime);
        }
    }
    void updateWindowEvents(float sensorValue) {
        for (auto& event : windowEvents) {
            event.check(sensorValue);
        }
    }

private:
    std::list<PeriodicEvent> periodicEvents;
    std::list<WindowEvent> windowEvents;
};

#endif // PROCESS_H
