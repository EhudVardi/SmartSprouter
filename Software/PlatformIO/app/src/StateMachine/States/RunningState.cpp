#include "StateMachine/States/RunningState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void RunningState::enter(SystemContext* context) {
    std::cout << "Entering Running State\n";
}

void RunningState::exit(SystemContext* context) {
    std::cout << "Exiting Running State\n";
}

void RunningState::update(SystemContext* context) {
    context->sensorManager->readSensors();
}

void RunningState::handleInput(SystemContext* context, InputEvent event) {
    switch (event) {
        case InputEvent::ButtonXPressed:
            std::cout << "Button X Pressed in Running State\n";
            // Logic for handling ButtonXPressed in Running State
            break;
        // Handle other input events
    }
}
