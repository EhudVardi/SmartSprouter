#include "StateMachine/App/AppStates.h"
#include <iostream>

void AbortingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Abort);
    if (!abortPage) {
        abortPage = context->displayManager->getPageAs<PageAppAbort>(Pages::Abort);
    }
	log("enter AbortingState");
}
void AbortingState::exit(SystemContext* context) {
    context->processManager->deleteCurrentProcess();
    context->processManager->deleteStoredProcess();
    context->actuatorManager->ShutDownAllActuators();
	log("exit AbortingState");
}
void AbortingState::update(SystemContext* context) {
    context->displayManager->refresh();
}
void AbortingState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Running, context);
    }
    else if (event == InputEvent::EnterPressed) {
        stateMachine->changeState(AppStates::Idling, context);
    }
}



void IdlingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Idle);
    if (!idlePage) {
        idlePage = context->displayManager->getPageAs<PageAppIdle>(Pages::Idle);
    }
	log("enter IdlingState");
}
void IdlingState::exit(SystemContext* context) {
	log("exit IdlingState");
}
void IdlingState::update(SystemContext* context) {
    if (idlePage) {
        idlePage->SetHumidity(context->sensorManager->getHumidity());
        idlePage->SetTemperature(context->sensorManager->getTemperature());
        idlePage->SetDateTime(context->timeManager->getCurrentTime());
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
	log("enter InformingState");
}
void InformingState::exit(SystemContext* context) {
	log("exit InformingState");
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
    if (context->processManager->loadProcessFromStorage(context->actuatorManager)) {
        stateMachine->changeState(AppStates::Running, context);
    } else {
        stateMachine->changeState(AppStates::Idling, context);
    }
}
void InitializingState::exit(SystemContext* context) {}
void InitializingState::update(SystemContext* context) {}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {}



void RunningState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Run);
    if (!runPage) {
        runPage = context->displayManager->getPageAs<PageAppRun>(Pages::Run);
    }
	log("enter RunningState");
}
void RunningState::exit(SystemContext* context) {
	log("exit RunningState");
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
	//log("update RunningState");
}
void RunningState::handleInput(SystemContext* context, InputEvent event) {
	if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::Aborting, context);
    }
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
	log("enter SettingProcessState");
}
void SettingProcessState::exit(SystemContext* context) {
	log("exit SettingProcessState");
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
    /// if any fails, then transite to SystemInError state.
    if (!context->inputManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitInputManager);
        return;
    }
    if (!context->sensorManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitSensorManager);
        return;
    }
    if (!context->displayManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitDisplayManager);
        return;
    }
    if (!context->actuatorManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitActuatorManager);
        return;
    }
    if (!context->processManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitProcessManager);
        return;
    }
    if (!context->networkManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitNetworkManager);
        return;
    }
    if (!context->timeManager->initialize()) {
        GoToErrorState(context, AppErrors::ErrInitTimeManager);
        return;
    }

    // attempt to update RTC from NTP service
    if (context->timeManager->UpdateRtcFromNtpService(context->networkManager)){
        log("update time from ntp service successful");
        log(context->timeManager->getCurrentTime().ToArduinoString());
    } else { 
        log("update time from ntp service failed"); 
    }

    // transite forward to Initializing state
    stateMachine->changeState(AppStates::Initializing, context);
}
void StartingUpState::exit(SystemContext* context) { }
void StartingUpState::update(SystemContext* context) { }
void StartingUpState::handleInput(SystemContext* context, InputEvent event) { }



void SystemInErrorState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Error);
}
void SystemInErrorState::exit(SystemContext* context) { }
void SystemInErrorState::update(SystemContext* context) {
    context->displayManager->refresh();
}
void SystemInErrorState::handleInput(SystemContext* context, InputEvent event) { }



DiagnosingState::DiagnosingState() {
    diagStateMachine.setOnExitDiagCallback(
        [this](SystemContext* context) {
            stateMachine->changeState(AppStates::Idling, context);
        });
}
void DiagnosingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::Diag);
    if (!diagPage) {
        diagPage = context->displayManager->getPageAs<PageAppDiag>(Pages::Diag);
    }
	diagStateMachine.changeState(DiagStates::HumidifiersSelected, context); // init nested diag state machine
}
void DiagnosingState::exit(SystemContext* context) { }
void DiagnosingState::update(SystemContext* context) {
	float humidity = context->sensorManager->getHumidity();
	float temperature = context->sensorManager->getTemperature();
    if (diagPage) {
        diagPage->SetHumidity(humidity);
        diagPage->SetTemperature(temperature);
        diagPage->SetDateTime(context->timeManager->getCurrentTime());
        context->displayManager->refresh();
    }
}
void DiagnosingState::handleInput(SystemContext* context, InputEvent event) {
    diagStateMachine.handleInput(event, context);
    update(context);
}
