#include "HWRotaryEncoderHandler.h"

HWRotaryEncoderHandler::HWRotaryEncoderHandler(
    const std::vector<std::tuple<int, int, int>>& encoderParams,
    const std::vector<std::function<void()>>& handlers_onRotateLeft,
    const std::vector<std::function<void()>>& handlers_onRotateRight,
    const std::vector<std::function<void()>>& handlers_onButtonPress,
    const std::vector<std::function<void()>>& handlers_onButtonRelease) {

    for (size_t i = 0; i < encoderParams.size(); ++i) {
        int pin1, pin2, buttonPin;
        std::tie(pin1, pin2, buttonPin) = encoderParams[i]; // Unpack parameters
        encoders.emplace_back(pin1, pin2, buttonPin); // Create and add HWRotaryEncoder

        // Set callbacks for the current encoder
        encoders[i].setOnRotateLeftCallback(handlers_onRotateLeft[i]);
        encoders[i].setOnRotateRightCallback(handlers_onRotateRight[i]);
        encoders[i].setOnButtonPressCallback(handlers_onButtonPress[i]);
        encoders[i].setOnButtonReleaseCallback(handlers_onButtonRelease[i]);
    }
}

void HWRotaryEncoderHandler::tickAll() {
    for (HWRotaryEncoder& encoder : encoders) {
        encoder.tick();
    }
}
