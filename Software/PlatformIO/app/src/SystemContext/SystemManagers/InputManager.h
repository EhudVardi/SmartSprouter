#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "BaseManager.h"

#include <map>
#include <functional>
#include "InputEvent.h" // Make sure to create this for the InputEvent enum

#include "HardwareAbstraction/HWButtonHandler.h"
#include "HardwareAbstraction/HWRotaryEncoderHandler.h"

class InputManager : public BaseManager {
private:
    std::map<InputEvent, std::function<void()>> eventHandlers;
    HWButtonHandler* hwButtonHandler = nullptr;
    HWRotaryEncoderHandler* encoderHandler = nullptr;

public:
    bool initialize() override;
    void registerEventHandler(InputEvent event, std::function<void()> handler);
    void pollInputs();
};

#endif // INPUT_MANAGER_H