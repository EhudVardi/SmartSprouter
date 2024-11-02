#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H

#include "Logic/Process/ActionableEvent.h"

class WindowEvent : public ActionableEvent<float> {
public:
    // Default constructor
    WindowEvent()
        : ActionableEvent<float>(
            [](float) { return false; },  // Default predicate always returns false
            []() {},                       // No-op start action
            []() {}),                      // No-op stop action
          lowThreshold(0.0f),             // Initialize to default threshold
          highThreshold(100.0f)           // Initialize to default threshold
    {}
    // Constructor with parameters
    WindowEvent(float p_lowThreshold, float p_highThreshold, std::function<void()> startAction, std::function<void()> stopAction)
        : ActionableEvent<float>(
            [this](float value) { 
                if (value < lowThreshold) {
                    return true; // Should activate
                } else if (value > highThreshold) {
                    return false; // Should deactivate
                } else {
                    return active; // Maintain current state if within thresholds (hysteresis)
                }
            },
            startAction, stopAction),
          lowThreshold(p_lowThreshold), highThreshold(p_highThreshold) { }

    // Implementing serialization
    uint8_t* serialize(uint8_t* buffer) const override {
        buffer = ActionableEvent::serialize(buffer);
        buffer = serializeMember(&lowThreshold, buffer);
        return serializeMember(&highThreshold, buffer);
    }
    const uint8_t* deserialize(const uint8_t* buffer) override {
        buffer = ActionableEvent::deserialize(buffer);
        buffer = deserializeMember(&lowThreshold, buffer);
        return deserializeMember(&highThreshold, buffer);
    }
    size_t getSerializedSize() const override {
        int size = ActionableEvent::getSerializedSize() + sizeof(lowThreshold) + sizeof(highThreshold);
        return size;
    }

    // equal operator overload
    bool operator==(const WindowEvent& other) const {
        return lowThreshold == other.lowThreshold &&
               highThreshold == other.highThreshold &&
               active == other.active;
    }
    
    String ToString() const {
        String str = "WindowEvent { ";
        str += "lowThreshold: " + String(lowThreshold) + ", ";
        str += "highThreshold: " + String(highThreshold) + ", ";
        str += "active: " + String(active ? "true" : "false") + " }";
        return str;
    }

private:
    float lowThreshold;
    float highThreshold;
};

#endif // WINDOWEVENT_H
