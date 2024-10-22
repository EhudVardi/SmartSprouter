#include "StateMachine/States/SettingProcessState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void SettingProcessState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Setup);
    if (!setupPage) {
        setupPage = context->displayManager->getPageAs<PageAppIdle>(Pages::Setup);
    }
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
        stateMachine->changeState(States::Idling, context);
    }
}
