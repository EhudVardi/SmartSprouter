#ifndef HWROTARYENCODERHANDLER_H
#define HWROTARYENCODERHANDLER_H

#include "HWRotaryEncoder.h"
#include <vector>
#include <tuple>
#include <functional>

class HWRotaryEncoderHandler {
public:
    // Constructor that accepts encoder parameters and their respective handlers
    HWRotaryEncoderHandler(const std::vector<std::tuple<int, int, int>>& encoderParams,
                           const std::vector<std::function<void()>>& handlers_onRotateLeft,
                           const std::vector<std::function<void()>>& handlers_onRotateRight,
                           const std::vector<std::function<void()>>& handlers_onButtonPress,
                           const std::vector<std::function<void()>>& handlers_onButtonRelease);

    // Call in the main loop to update all encoders
    void tickAll();

private:
    std::vector<HWRotaryEncoder> encoders; // Store HWRotaryEncoder objects
};

#endif // HWROTARYENCODERHANDLER_H
