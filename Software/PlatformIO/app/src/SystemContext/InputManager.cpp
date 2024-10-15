#include "SystemContext/InputManager.h"

bool InputManager::initialize() {
    
    /// initialize simple buttons
    std::vector<int> hwButtonPins = { 12 };
    std::vector<std::function<void()>> hwButtonHandlers_onPress = {
        []() { std::cout << "testing button - pressed" << std::endl; },
    };
    std::vector<std::function<void()>> hwButtonHandlers_onRelease = {
        []() { std::cout << "testing button - released" << std::endl; },
    };
    hwButtonHandler = new HWButtonHandler(hwButtonPins, hwButtonHandlers_onPress, hwButtonHandlers_onRelease);
    
    /// initialize rotary encoders
    std::vector<std::tuple<int, int, int>> encoderParams = {
        {18, 19, 21}, // Encoder 1
    };
    std::vector<std::function<void()>> handlers_onRotateLeft = {
        []() { std::cout << "Encoder 1 Rotated Left" << std::endl; },
    };
    std::vector<std::function<void()>> handlers_onRotateRight = {
        []() { std::cout << "Encoder 1 Rotated Right" << std::endl; },
    };
    std::vector<std::function<void()>> handlers_onButtonPress = {
        []() { std::cout << "Encoder 1 Button Pressed" << std::endl; },
    };
    std::vector<std::function<void()>> handlers_onButtonRelease = {
        []() { std::cout << "Encoder 1 Button Released" << std::endl; },
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

    // // In a real system, this would read from hardware inputs.
    // // Simulate an input event
    // if (eventHandlers.count(InputEvent::ButtonXPressed)) {
    //     eventHandlers[InputEvent::ButtonXPressed]();  // Trigger the event handler
    // }
}
