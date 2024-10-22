#include "StateMachine/App/States/IdlingState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void IdlingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Idle);
    if (!idlePage) {
        idlePage = context->displayManager->getPageAs<PageAppIdle>(Pages::Idle);
    }
	std::cout << "enter IdlingState" << std::endl;
}

void IdlingState::exit(SystemContext* context) {
	std::cout << "exit IdlingState" << std::endl;
}

void IdlingState::update(SystemContext* context) {
    if (idlePage) {
        idlePage->SetHumidity(context->sensorManager->getHumidity());
        idlePage->SetTemperature(context->sensorManager->getTemperature());
        context->displayManager->refresh();
    }
}

void IdlingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::RotatedRight) {
        stateMachine->changeState(AppStates::Informing, context);
    }
    else if (event == InputEvent::EnterPressed) {
        stateMachine->changeState(AppStates::SettingProcess, context);
    }
}
