#include "SystemContext/InputManager.h"

bool InputManager::initialize() {
    
    /// initialize simple buttons
    std::vector<int> hwButtonPins = { 12 };
    std::vector<std::function<void()>> hwButtonHandlers_onPress = {
        [this]() {     
            if (eventHandlers.count(InputEvent::BackPressed)) {
                eventHandlers[InputEvent::BackPressed]();
            }
        },
    };
    std::vector<std::function<void()>> hwButtonHandlers_onRelease = {
        [this]() {     
            if (eventHandlers.count(InputEvent::BackReleased)) {
                eventHandlers[InputEvent::BackReleased]();
            }
        },
    };
    hwButtonHandler = new HWButtonHandler(hwButtonPins, hwButtonHandlers_onPress, hwButtonHandlers_onRelease);
    
    /// initialize rotary encoders
    std::vector<std::tuple<int, int, int>> encoderParams = {
        {18, 19, 21}, // Encoder 1
    };
    std::vector<std::function<void()>> handlers_onRotateLeft = {
        [this]() {     
            if (eventHandlers.count(InputEvent::RotatedLeft)) {
                eventHandlers[InputEvent::RotatedLeft]();
            }
        },
    };
    std::vector<std::function<void()>> handlers_onRotateRight = {
        [this]() {     
            if (eventHandlers.count(InputEvent::RotatedRight)) {
                eventHandlers[InputEvent::RotatedRight]();
            }
        },
    };
    std::vector<std::function<void()>> handlers_onButtonPress = {
        [this]() {     
            if (eventHandlers.count(InputEvent::EnterPressed)) {
                eventHandlers[InputEvent::EnterPressed]();
            }
        },
    };
    std::vector<std::function<void()>> handlers_onButtonRelease = {
        [this]() {     
            if (eventHandlers.count(InputEvent::EnterReleased)) {
                eventHandlers[InputEvent::EnterReleased]();
            }
        },
    };
    encoderHandler = new HWRotaryEncoderHandler(encoderParams, handlers_onRotateLeft, handlers_onRotateRight, handlers_onButtonPress, handlers_onButtonRelease);
    
    return true;
}

void InputManager::registerEventHandler(InputEvent event, std::function<void()> handler) {
    eventHandlers[event] = handler;
}

void InputManager::pollInputs() {
    hwButtonHandler->updateButtons();
    encoderHandler->tickAll();
}
