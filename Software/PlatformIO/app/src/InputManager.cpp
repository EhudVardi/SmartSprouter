#include "InputManager.h"
#include <iostream>

void InputManager::registerEventHandler(InputEvent event, std::function<void()> handler) {
    eventHandlers[event] = handler;
}

void InputManager::pollInputs() {
    // In a real system, this would read from hardware inputs.
    // Simulate an input event
    if (eventHandlers.count(InputEvent::ButtonXPressed)) {
        eventHandlers[InputEvent::ButtonXPressed]();  // Trigger the event handler
    }
}
