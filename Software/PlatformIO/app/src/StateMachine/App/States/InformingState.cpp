#include "StateMachine/States/InformingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void InformingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::About);
	std::cout << "enter InformingState" << std::endl;
}

void InformingState::exit(SystemContext* context) {
	std::cout << "exit InformingState" << std::endl;
}

void InformingState::update(SystemContext* context) {
    context->displayManager->refresh();
}

void InformingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::RotatedLeft) {
        stateMachine->changeState(States::Idling, context);
    }
}
