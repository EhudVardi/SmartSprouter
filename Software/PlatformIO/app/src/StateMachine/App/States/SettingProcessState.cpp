#include "StateMachine/App/States/SettingProcessState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

SettingProcessState::SettingProcessState() {
    setupStateMachine.setOnStartEnterCallback(
        [this](SystemContext* context) {
            stateMachine->changeState(AppStates::Running, context);
        });
}

void SettingProcessState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Setup);
    if (!setupPage) {
        setupPage = context->displayManager->getPageAs<PageAppIdle>(Pages::Setup);
    }
    setupStateMachine.changeState(SetupStates::HumidityRangeSelect, context); // init nested setup state machine state to initial state
	std::cout << "enter SettingProcessState" << std::endl;
}

void SettingProcessState::exit(SystemContext* context) {
	std::cout << "exit SettingProcessState" << std::endl;
}

void SettingProcessState::update(SystemContext* context) {
    if (setupPage) {
        
        context->displayManager->refresh();
    }
}

void SettingProcessState::handleInput(SystemContext* context, InputEvent event) {
    if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Idling, context);
    }
    else { // pass event into nested setup state machine
        setupStateMachine.handleInput(event, context);
        update(context);
    }
}
