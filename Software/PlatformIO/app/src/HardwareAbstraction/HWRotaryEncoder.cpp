#include "HWRotaryEncoder.h"

HWRotaryEncoder::HWRotaryEncoder(int pin1, int pin2, int buttonPin)
    : encoder(pin1, pin2), button(buttonPin) {
}

void HWRotaryEncoder::tick() {

    /// handle encoder rotation
    encoder.tick();
    long newPos = encoder.getPosition();
    if (newPos != lastPosition) {
        if (newPos > lastPosition && onRotateRight) {
            onRotateRight();
        }
        else if (newPos < lastPosition && onRotateLeft) {
            onRotateLeft();
        }
        lastPosition = newPos;
    }

    //handle button
    button.updateState();
}

void HWRotaryEncoder::setOnRotateLeftCallback(std::function<void()> callback) {
    onRotateLeft = callback;
}
void HWRotaryEncoder::setOnRotateRightCallback(std::function<void()> callback) {
    onRotateRight = callback;
}
void HWRotaryEncoder::setOnButtonPressCallback(std::function<void()> callback) {
    button.onPress = callback;
}
void HWRotaryEncoder::setOnButtonReleaseCallback(std::function<void()> callback) {
    button.onRelease = callback;
}
