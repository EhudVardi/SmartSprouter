#include "StateMachine/States/IdlingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void IdlingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Idle);
	std::cout << "enter IdlingState" << std::endl;
}

void IdlingState::exit(SystemContext* context) {
	std::cout << "exit IdlingState" << std::endl;
}

void IdlingState::update(SystemContext* context) {
    context->displayManager->refresh();
}

void IdlingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::RotatedRight) {
        stateMachine->changeState(States::Informing, context);
    }
}
