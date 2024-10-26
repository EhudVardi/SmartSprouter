#include "StateMachine/App/AppStates.h"
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
    else if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Diagnosing, context);
    }
}



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
        stateMachine->changeState(AppStates::Idling, context);
    }
}



void InitializingState::enter(SystemContext* context) {
    /// StateLogic:
    /// <TODO> check in memory if an unfinished process exists
    /// <TODO> if exist then load it into current process and transition into running state
    /// otherwise, transition into idle state
    stateMachine->changeState(AppStates::Idling, context);
}
void InitializingState::exit(SystemContext* context) {}
void InitializingState::update(SystemContext* context) {}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {}



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



void StartingUpState::enter(SystemContext* context) {
    /// StateLogic:
    /// initialize all managers in the system context object
    /// if any fails, then transite to SystemInError state. else transite forward to Initializing state
    if (!context->inputManager->initialize()) {
        stateMachine->changeState(AppStates::SystemInError, context);
        return;
    }
    if (!context->sensorManager->initialize()) {
        stateMachine->changeState(AppStates::SystemInError, context);
        return;
    }
    if (!context->displayManager->initialize()) {
        stateMachine->changeState(AppStates::SystemInError, context);
        return;
    }
    if (!context->actuatorManager->initialize()) {
        stateMachine->changeState(AppStates::SystemInError, context);
        return;
    }
    if (!context->processManager->initialize()) {
        stateMachine->changeState(AppStates::SystemInError, context);
        return;
    }
    stateMachine->changeState(AppStates::Initializing, context);
}
void StartingUpState::exit(SystemContext* context) { }
void StartingUpState::update(SystemContext* context) { }
void StartingUpState::handleInput(SystemContext* context, InputEvent event) { }



void SystemInErrorState::enter(SystemContext* context) { }
void SystemInErrorState::exit(SystemContext* context) { }
void SystemInErrorState::update(SystemContext* context) { }
void SystemInErrorState::handleInput(SystemContext* context, InputEvent event) { }



void DiagnosingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Diag);
    if (!diagPage) {
        diagPage = context->displayManager->getPageAs<PageAppDiag>(Pages::Diag);
        DisplayDate date(1,1,2024);
        diagPage->SetDate(date);
    }
	std::cout << "enter DiagnosingState" << std::endl;
}
void DiagnosingState::exit(SystemContext* context) {
	std::cout << "exit DiagnosingState" << std::endl;
}
void DiagnosingState::update(SystemContext* context) {
	float humidity = context->sensorManager->getHumidity();
	float temperature = context->sensorManager->getTemperature();
    if (diagPage) {
        diagPage->SetHumidity(humidity);
        diagPage->SetTemperature(temperature);
        diagPage->TickTime();
        context->displayManager->refresh();
    }
	//std::cout << "update DiagnosingState" << std::endl;
}
void DiagnosingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Idling, context);
    }
	std::cout << "handleInput DiagnosingState" << std::endl;
}
