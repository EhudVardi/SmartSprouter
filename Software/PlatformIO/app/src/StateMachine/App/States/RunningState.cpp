#include "StateMachine/App/States/RunningState.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void RunningState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Run);
    if (!runPage) {
        runPage = context->displayManager->getPageAs<PageAppRun>(Pages::Run);
    }
	std::cout << "enter RunningState" << std::endl;
}

void RunningState::exit(SystemContext* context) {
	std::cout << "exit RunningState" << std::endl;
}

void RunningState::update(SystemContext* context) {
	float humidity = context->sensorManager->getHumidity();
	float temperature = context->sensorManager->getTemperature();
	//TODO: make decisions and update actuators
    if (runPage) {
        runPage->SetHumidity(humidity);
        runPage->SetTemperature(temperature);
        context->displayManager->refresh();
    }
	std::cout << "update RunningState" << std::endl;
}

void RunningState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Aborting, context);
    }
	std::cout << "handleInput RunningState" << std::endl;
}
