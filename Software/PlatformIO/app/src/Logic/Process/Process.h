#ifndef PROCESS_H
#define PROCESS_H

#include "Logic/Process/PeriodicEvent.h"
#include "Logic/Process/WindowEvent.h"
#include "Data/Serialization/ISerializable.h"
#include "Logic/Process/ProcessEvents.h"
#include "Data/EnumHelpers.h"
#include <unordered_map>
#include <Arduino.h>

class Process : public ISerializable {
public:
    Process() {}
    Process(AppTimeSpan duration, AppDateTime start)
        : totalDuration(duration), remainingDuration(duration), startTime(start) {}

    void addPeriodicEvent(PeriodicEvents key, const PeriodicEvent& event) {
        periodicEvents[key] = event;
    }
    void addWindowEvent(WindowEvents key, const WindowEvent& event) {
        windowEvents[key] = event;
    }

    PeriodicEvent* getPeriodicEvent(PeriodicEvents eventKey) {
        auto it = periodicEvents.find(eventKey);
        if (it != periodicEvents.end()) {
            return &it->second;
        }
        return nullptr;
    }
    WindowEvent* getWindowEvent(WindowEvents eventKey) {
        auto it = windowEvents.find(eventKey);
        if (it != windowEvents.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void updatePeriodicEvent(PeriodicEvents eventKey, AppDateTime currentTime) {
        auto it = periodicEvents.find(eventKey);
        if (it != periodicEvents.end()) {
            it->second.check(currentTime);
        }
    }
    void updateWindowEvent(WindowEvents eventKey, float sensorValue) {
        auto it = windowEvents.find(eventKey);
        if (it != windowEvents.end()) {
            it->second.check(sensorValue);
        }
    }

    const AppTimeSpan updateRemainingDuration(const AppTimeSpan& passedTime) {
        remainingDuration = remainingDuration - passedTime;
        return remainingDuration;
    }
    
    // Implementing serialization
    virtual uint8_t* serialize(uint8_t* buffer) const override {
        uint8_t* ptr = buffer;

        ptr = serializeMember(&startTime, ptr);
        ptr = serializeMember(&totalDuration, ptr);
        ptr = serializeMember(&remainingDuration, ptr);

        size_t periodicEventCount = periodicEvents.size();
        ptr = serializeMember(&periodicEventCount, ptr);
        for (const auto& pair : periodicEvents) {
            ptr = serializeMember(&pair.first, ptr);
            ptr = pair.second.serialize(ptr);
        }

        size_t windowEventCount = windowEvents.size();
        ptr = serializeMember(&windowEventCount, ptr);
        for (const auto& pair : windowEvents) {
            ptr = serializeMember(&pair.first, ptr);
            ptr = pair.second.serialize(ptr);
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
        for (size_t i = 0; i < periodicEventCount; ++i) {
            PeriodicEvents key;
            ptr = deserializeMember(&key, ptr);
            PeriodicEvent event;
            ptr = event.deserialize(ptr);
            periodicEvents[key] = event;
        }

        size_t windowEventCount;
        ptr = deserializeMember(&windowEventCount, ptr);
        windowEvents.clear();
        for (size_t i = 0; i < windowEventCount; ++i) {
            WindowEvents key;
            ptr = deserializeMember(&key, ptr);
            WindowEvent event;
            ptr = event.deserialize(ptr);
            windowEvents[key] = event;
        }

        return ptr;
    }

    virtual size_t getSerializedSize() const override {
        size_t size = 0;

        size += sizeof(startTime);
        size += sizeof(totalDuration);
        size += sizeof(remainingDuration);

        size += sizeof(size_t); // For periodicEventCount
        for (const auto& pair : periodicEvents) {
            size += sizeof(uint8_t); // Size of ProcessEvents
            size += pair.second.getSerializedSize();
        }

        size += sizeof(size_t); // For windowEventCount
        for (const auto& pair : windowEvents) {
            size += sizeof(uint8_t); // Size of ProcessEvents
            size += pair.second.getSerializedSize();
        }

        return size;
    }

    // Equal operator overload
    bool operator==(const Process& other) const {
        // Compare local members
        if (startTime != other.startTime) return false;
        if (totalDuration != other.totalDuration) return false;
        if (remainingDuration != other.remainingDuration) return false;

        // Compare periodicEvents maps
        if (periodicEvents.size() != other.periodicEvents.size()) return false;
        for (const auto& pair : periodicEvents) {
            const auto& key = pair.first;
            const auto& event = pair.second;
            auto it = other.periodicEvents.find(key);
            if (it == other.periodicEvents.end() || it->second != event) {
                return false;
            }
        }

        // Compare windowEvents maps
        if (windowEvents.size() != other.windowEvents.size()) return false;
        for (const auto& pair : windowEvents) {
            const auto& key = pair.first;
            const auto& event = pair.second;
            auto it = other.windowEvents.find(key);
            if (it == other.windowEvents.end() || it->second != event) {
                return false;
            }
        }

        return true;
    }
    
    bool operator!=(const Process& other) const {
        return !(*this == other);
    }
    
    String ToString() const {
        String str = "Process { ";

        str += "startTime: " + startTime.ToString() + ", ";
        str += "totalDuration: " + totalDuration.ToString() + ", ";
        str += "remainingDuration: " + remainingDuration.ToString() + ", ";

        // Add periodic events
        str += "periodicEvents: { ";
        for (const auto& pair : periodicEvents) {
            str += "ProcessEvents::" + String(EnumHelpers::PeriodicEventsHelper.ToString(pair.first)) + ": " + pair.second.ToString() + ", ";
        }
        str += "}, ";
        // Add window events
        str += "windowEvents: { ";
        for (const auto& pair : windowEvents) {
            str += "ProcessEvents::" + String(EnumHelpers::WindowEventsHelper.ToString(pair.first)) + ": " + pair.second.ToString() + ", ";
        }
        str += "} ";

        str += "}";
        return str;
    }

private:
    AppDateTime startTime;
    AppTimeSpan totalDuration;
    AppTimeSpan remainingDuration;
    std::unordered_map<PeriodicEvents, PeriodicEvent> periodicEvents;
    std::unordered_map<WindowEvents, WindowEvent> windowEvents;
};

#endif // PROCESS_H
