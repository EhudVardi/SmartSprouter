#include "ConfirmState.h"
#include "SystemContext.h"
#include <iostream>

void ConfirmState::enter(SystemContext* context) {
    std::cout << "Entering Confirm State\n";
    context->displayManager->showPage("Confirm Page");
}

void ConfirmState::exit(SystemContext* context) {
    std::cout << "Exiting Confirm State\n";
}

void ConfirmState::update(SystemContext* context) {
    // Confirm state logic
}

void ConfirmState::handleInput(SystemContext* context, InputEvent event) {
    switch (event) {
        case InputEvent::ButtonXPressed:
            std::cout << "User confirms in Confirm State\n";
            // Handle confirmation, transition to new state if necessary
            break;
        // Handle other input events
    }
}
