#include "StateMachine/App/States/AbortingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void AbortingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Abort);
    if (!abortPage) {
        abortPage = context->displayManager->getPageAs<PageAppAbort>(Pages::Abort);
    }
	std::cout << "enter AbortingState" << std::endl;
}

void AbortingState::exit(SystemContext* context) {
	std::cout << "exit AbortingState" << std::endl;
}

void AbortingState::update(SystemContext* context) {
    context->displayManager->refresh();
	std::cout << "update RunningState" << std::endl;
}

void AbortingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Running, context);
    }
    else if (event == InputEvent::EnterPressed) {
        stateMachine->changeState(AppStates::Idling, context);
    }
	std::cout << "handleInput AbortingState" << std::endl;
}
