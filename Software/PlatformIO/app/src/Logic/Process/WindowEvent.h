#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H

#include "Logic/Process/ActionableEvent.h"

class WindowEvent : public ActionableEvent<float> {
public:
    WindowEvent(float p_lowThreshold, float p_highThreshold, std::function<void()> startAction, std::function<void()> stopAction)
        : ActionableEvent<float>(
            [this](float value) { 
                // Predicate: Activate if humidity is below lowThreshold, Deactivate if humidity is above highThreshold
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

private:
    float lowThreshold;
    float highThreshold;
};

#endif // WINDOWEVENT_H
