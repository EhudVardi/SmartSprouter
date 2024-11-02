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

    void updatePeriodicEvents(DisplayDateTime currentTime) {
        for (auto& event : periodicEvents) {
            event.update(currentTime);
        }
    }
    void updateWindowEvents(float sensorValue) {
        for (auto& event : windowEvents) {
            event.check(sensorValue);
        }
    }
    
    void serialize(uint8_t* buffer) const override {

        // Serialize the size of periodicEvents
        size_t periodicEventsSize = periodicEvents.size();
        buffer = serializeMember(&periodicEventsSize, sizeof(periodicEventsSize), buffer);
        // Serialize each periodic event
        for (const auto& event : periodicEvents) {
            event.serialize(buffer);
        }
        
        // Serialize the size of windowEvents
        size_t windowEventsSize = windowEvents.size();
        buffer = serializeMember(&windowEventsSize, sizeof(windowEventsSize), buffer);
        // Serialize each window event
        for (const auto& event : windowEvents) {
            event.serialize(buffer);
        }
    }
    void deserialize(const uint8_t* buffer) override {

        // Deserialize the size of periodicEvents
        size_t periodicEventsSize;
        buffer = deserializeMember(&periodicEventsSize, sizeof(periodicEventsSize), buffer);
        periodicEvents.clear();
        for (size_t i = 0; i < periodicEventsSize; ++i) {
            PeriodicEvent event;
            event.deserialize(buffer);
            periodicEvents.push_back(event);
        }

        // Deserialize the size of windowEvents
        size_t windowEventsSize;
        buffer = deserializeMember(&windowEventsSize, sizeof(windowEventsSize), buffer);
        windowEvents.clear();
        for (size_t i = 0; i < windowEventsSize; ++i) {
            WindowEvent event;
            event.deserialize(buffer);
            windowEvents.push_back(event);
        }

    // equal operator overload
    bool operator==(const Process& other) const {
        
        // Compare periodicEvents lists
        if (periodicEvents.size() != other.periodicEvents.size()) return false;
        if (!std::equal(periodicEvents.begin(), periodicEvents.end(), other.periodicEvents.begin())) return false;
        
        // Compare windowEvents lists
        if (windowEvents.size() != other.windowEvents.size()) return false;
        if (!std::equal(windowEvents.begin(), windowEvents.end(), other.windowEvents.begin())) return false;
        
        return true;
    }
    bool operator!=(const Process& other) const {
        return !(*this == other);
    }

private:
    std::list<PeriodicEvent> periodicEvents;
    std::list<WindowEvent> windowEvents;
};

#endif // PROCESS_H
