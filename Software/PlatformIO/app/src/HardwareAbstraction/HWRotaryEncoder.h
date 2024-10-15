#ifndef HWROTARYENCODER_H
#define HWROTARYENCODER_H

#include <RotaryEncoder.h>
#include <functional>

#include "HardwareAbstraction/HWButton.h"

class HWRotaryEncoder {
public:
    // Constructor to initialize the encoder with rotary pins and button pin
    HWRotaryEncoder(int pin1, int pin2, int buttonPin);

    // Methods to be called in the main loop
    void tick();

    // Event registration for handling rotation and button press
    void setOnRotateLeftCallback(std::function<void()> callback);
    void setOnRotateRightCallback(std::function<void()> callback);
    void setOnButtonPressCallback(std::function<void()> callback);
    void setOnButtonReleaseCallback(std::function<void()> callback);

private:
    RotaryEncoder encoder;
    HWButton button;

    // Internal callback functions
    std::function<void()> onRotateLeft;
    std::function<void()> onRotateRight;
    std::function<void()> onButtonPress;
    std::function<void()> onButtonRelease;

    // Tracks the last encoder position
    long lastPosition;
};

#endif // HWROTARYENCODER_H
