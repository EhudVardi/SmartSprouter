#ifndef HW_BUTTON_H
#define HW_BUTTON_H

#include <Arduino.h>
#include <functional>

enum class HWButtonState {
    Released,
    Pressed
};

// HWButton class to represent individual buttons
class HWButton {
public:
    int pin;
    volatile HWButtonState state;
    volatile HWButtonState lastState;
    std::function<void()> onPress; // press Event handler
    std::function<void()> onRelease; // release Event handler

    // Debounce parameters
    unsigned long lastDebounceTime; // Last time the button state changed
    const unsigned long debounceDelay = 50; // Debounce delay in milliseconds
    int lastReading; // Last stable reading from the button pin

    HWButton(int pin); // init new button with a given gpio pin number
    HWButtonState getState(); // Get button current state
    void updateState(); // Update the button state with debounce logic
};

#endif // HW_BUTTON_H
