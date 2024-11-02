#ifndef PROCESS_H
#define PROCESS_H

#include "Logic/Process/PeriodicEvent.h"
#include "Logic/Process/WindowEvent.h"
#include "Data/ISerializable.h"
#include <vector>

class Process : public ISerializable {
public:
    Process() {}
    Process(DisplayTimeSpan duration, DisplayDateTime start) 
        : totalDuration(duration), remainingDuration(duration), startTime(start) {}

    void addPeriodicEvent(const PeriodicEvent& event) {
        periodicEvents.push_back(event);
    }
    void addWindowEvent(const WindowEvent& event) {
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

        ptr = serializeMember(&startTime, ptr);
        ptr = serializeMember(&totalDuration, ptr);
        ptr = serializeMember(&remainingDuration, ptr);

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

        ptr = deserializeMember(&startTime, ptr);
        ptr = deserializeMember(&totalDuration, ptr);
        ptr = deserializeMember(&remainingDuration, ptr);

        size_t periodicEventCount;
        ptr = deserializeMember(&periodicEventCount, ptr);
        periodicEvents.clear();
        periodicEvents.reserve(periodicEventCount);
        for (size_t i = 0; i < periodicEventCount; ++i) {
            PeriodicEvent event;
            ptr = event.deserialize(ptr);
            periodicEvents.push_back(event);
        }

        size_t windowEventCount; 
        ptr = deserializeMember(&windowEventCount, ptr);
        windowEvents.clear();
        windowEvents.reserve(windowEventCount);
        for (size_t i = 0; i < windowEventCount; ++i) {
            WindowEvent event;
            ptr = event.deserialize(ptr);
            windowEvents.push_back(event);
        }

        return ptr; // Return the updated pointer
    }
    virtual size_t getSerializedSize() const override {

        size_t size = 0;

        size += sizeof(startTime);
        size += sizeof(totalDuration);
        size += sizeof(remainingDuration);

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

        // compare local members
        if (startTime != other.startTime) return false;
        if (totalDuration != other.totalDuration) return false;
        if (remainingDuration != other.remainingDuration) return false;
        
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
    DisplayDateTime startTime;
    DisplayTimeSpan totalDuration;
    DisplayTimeSpan remainingDuration;
    std::vector<PeriodicEvent> periodicEvents;
    std::vector<WindowEvent> windowEvents;
};

#endif // PROCESS_H
