#include "StateMachine/App/States/RunningState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void RunningState::enter(SystemContext* context) {
	std::cout << "enter RunningState" << std::endl;
}

void RunningState::exit(SystemContext* context) {
	std::cout << "exit RunningState" << std::endl;
}

void RunningState::update(SystemContext* context) {
	std::cout << "update RunningState" << std::endl;
}

void RunningState::handleInput(SystemContext* context, InputEvent event) {
	std::cout << "handleInput RunningState" << std::endl;
}
