#include "StateMachine/States/IdlingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void IdlingState::enter(SystemContext* context) {
	std::cout << "enter IdlingState" << std::endl;
}

void IdlingState::exit(SystemContext* context) {
	std::cout << "exit IdlingState" << std::endl;
}

void IdlingState::update(SystemContext* context) {
    static int temp = 0;
    temp++;
    if (!(temp % 1000)) {
        std::cout << "update IdlingState" << std::endl;
    }
}

void IdlingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::RotatedRight) {
        stateMachine->changeState(States::Informing, context);
    }
}
