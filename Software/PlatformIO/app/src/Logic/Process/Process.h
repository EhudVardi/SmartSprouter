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
    
    // Implementing serialization
    virtual uint8_t* serialize(uint8_t* buffer) const override {
        uint8_t* ptr = buffer;

        size_t periodicEventCount = periodicEvents.size();
        ptr = serializeMember(&periodicEventCount, ptr);
        for (const auto& event : periodicEvents) {
            ptr = event.serialize(ptr);
        }

        size_t windowEventCount = windowEvents.size();
        ptr = serializeMember(&windowEventCount, ptr);
        for (const auto& event : windowEvents) {
            ptr = event.serialize(ptr);
        }

        return ptr;
    }
    virtual const uint8_t* deserialize(const uint8_t* buffer) override {
        const uint8_t* ptr = buffer;

        size_t periodicEventCount;
        ptr = deserializeMember(&periodicEventCount, ptr);
        periodicEvents.clear();
        for (size_t i = 0; i < periodicEventCount; ++i) {
            PeriodicEvent event;
            ptr = event.deserialize(ptr);
            periodicEvents.push_back(event);
        }

        size_t windowEventCount; 
        ptr = deserializeMember(&windowEventCount, ptr);
        windowEvents.clear();
        for (size_t i = 0; i < windowEventCount; ++i) {
            WindowEvent event;
            ptr = event.deserialize(ptr);
            windowEvents.push_back(event);
        }

        return ptr; // Return the updated pointer
    }
    virtual size_t getSerializedSize() const override {

        size_t size = 0;

        size += sizeof(size_t); // For periodicEventCount
        for (const auto& event : periodicEvents) {
            size += event.getSerializedSize();
        }

        size += sizeof(size_t); // For windowEventCount
        for (const auto& event : windowEvents) {
            size += event.getSerializedSize();
        }

        return size;
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
