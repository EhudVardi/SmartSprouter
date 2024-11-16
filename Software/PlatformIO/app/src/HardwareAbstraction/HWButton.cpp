# include "HWButton.h"

HWButton::HWButton(int pin)
    : pin(pin), state(HWButtonState::Released), lastState(HWButtonState::Released), lastReading(HIGH), lastDebounceTime(0) {
    pinMode(pin, INPUT_PULLUP);
}

HWButtonState HWButton::getState() {
    return state;
}

void HWButton::updateState() {
    // Read digital value
    int currentReading = digitalRead(pin);
    // Check if the reading has changed (due to noise or press)
    if (currentReading != lastReading) {
        lastDebounceTime = millis();  // Reset the debounce timer
    }
    // Only update the button state if enough time has passed (debounce)
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // State has been stable for the debounce delay, so update the button state
        HWButtonState currentState = (currentReading == LOW) ? HWButtonState::Pressed : HWButtonState::Released;
        if (currentState != state) {
            state = currentState;
            // Call the event handler if the button is pressed
            if (state == HWButtonState::Pressed && onPress) {
                onPress();
            }
            else if (state == HWButtonState::Released && onRelease) {
                onRelease();
            }
        }
    }
    lastReading = currentReading;  // Update lastReading for the next iteration
}