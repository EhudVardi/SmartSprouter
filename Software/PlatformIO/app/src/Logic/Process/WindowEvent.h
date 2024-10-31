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

    void serialize(uint8_t* buffer) const override {
        ActionableEvent<float>::serialize(buffer);
        buffer = serializeMember(&lowThreshold, sizeof(lowThreshold), buffer);
        buffer = serializeMember(&highThreshold, sizeof(highThreshold), buffer);
    }
    void deserialize(const uint8_t* buffer) override {
        ActionableEvent<float>::deserialize(buffer);
        buffer = deserializeMember(&lowThreshold, sizeof(lowThreshold), buffer);
        buffer = deserializeMember(&highThreshold, sizeof(highThreshold), buffer);
    }

private:
    float lowThreshold;
    float highThreshold;
};

#endif // WINDOWEVENT_H
