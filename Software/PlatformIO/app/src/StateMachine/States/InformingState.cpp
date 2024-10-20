#include "StateMachine/States/InformingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void InformingState::enter(SystemContext* context) {
	std::cout << "enter InformingState" << std::endl;
}

void InformingState::exit(SystemContext* context) {
	std::cout << "exit InformingState" << std::endl;
}

void InformingState::update(SystemContext* context) {
    static int temp = 0;
    temp++;
    if (!(temp % 1000)) {
	    std::cout << "update InformingState" << std::endl;
    }
}

void InformingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::RotatedLeft) {
        stateMachine->changeState(States::Idling, context);
    }
}
