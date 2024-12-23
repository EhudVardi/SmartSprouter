#include "AppStates.h"

void AbortingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::ABORT);
    if (!abortPage) {
        abortPage = context->displayManager->getPageAs<PageAppAbort>(Pages::ABORT);
    }
    log("enter AbortingState");
}
void AbortingState::exit(SystemContext* context) {
    log("exit AbortingState");
}
void AbortingState::update(SystemContext* context) {
    context->displayManager->refresh();
}
void AbortingState::handleInput(SystemContext* context, InputEvent event) {
    if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::RUNNING, context);
    }
    else if (event == InputEvent::EnterPressed) {
        context->processManager->deleteCurrentProcess();
        context->processManager->deleteStoredProcess();
        context->actuatorManager->ShutDownAllActuators();
        stateMachine->changeState(AppStates::IDLING, context);
    }
}



void IdlingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::IDLE);
    if (!idlePage) {
        idlePage = context->displayManager->getPageAs<PageAppIdle>(Pages::IDLE);
    }
    log("enter IdlingState");
}
void IdlingState::exit(SystemContext* context) {
    log("exit IdlingState");
}
void IdlingState::update(SystemContext* context) {
    if (idlePage) {
        float humidity, temperature;
        context->sensorManager->getHumidity(humidity);
        context->sensorManager->getTemperature(temperature);
        idlePage->SetHumidity(humidity);
        idlePage->SetTemperature(temperature);
        idlePage->SetDateTime(context->timeManager->getCurrentTime());
        context->displayManager->refresh();
    }
}
void IdlingState::handleInput(SystemContext* context, InputEvent event) {
    if (event == InputEvent::RotatedRight) {
        stateMachine->changeState(AppStates::INFORMING, context);
    }
    else if (event == InputEvent::EnterPressed) {
        stateMachine->changeState(AppStates::SETTING_PROCESS, context);
    }
    else if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::DIAGNOSING, context);
    }
}



void InformingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::ABOUT);
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
        stateMachine->changeState(AppStates::IDLING, context);
    }
}



void InitializingState::enter(SystemContext* context) {
    if (context->processManager->loadProcessFromStorage(context->timeManager->getCurrentTime(), context->actuatorManager)) {
        stateMachine->changeState(AppStates::RUNNING, context);
    }
    else {
        stateMachine->changeState(AppStates::IDLING, context);
    }
}
void InitializingState::exit(SystemContext* context) {}
void InitializingState::update(SystemContext* context) {}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {}



void RunningState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::RUN);
    if (!runPage) {
        runPage = context->displayManager->getPageAs<PageAppRun>(Pages::RUN);
    }
    if (!storeProcessTimer) {
        storeProcessTimer = new Timer(STORE_PROCESS_INTERVAL);
        storeProcessTimer->setCallback([context]() {
            if (context)
                context->processManager->storeCurrentProcess();
        });
    }
    storeProcessTimer->start();
    log("enter RunningState");
}
void RunningState::exit(SystemContext* context) {
    storeProcessTimer->stop();
    log("exit RunningState");
}
void RunningState::update(SystemContext* context) {

    float humidity, temperature;
    bool humidityValid = context->sensorManager->getHumidity(humidity);
    bool temperatureValid = context->sensorManager->getTemperature(temperature);

    AppTimeSpan remainingTime = context->processManager->updateProcess(context->timeManager->getCurrentTime(), humidity, temperature);
    if (remainingTime.totalseconds() <= 0) {
        log("RunningState: process finished successfully");
        //TODO: log results
        context->processManager->deleteCurrentProcess();
        context->processManager->deleteStoredProcess();
        context->actuatorManager->ShutDownAllActuators();
        stateMachine->changeState(AppStates::IDLING, context); //TODO: goto summery page/state ?
    }
    else {
        if (runPage) {
            if (humidityValid) runPage->SetHumidity(humidity);
            if (temperatureValid) runPage->SetTemperature(temperature);
            runPage->SetDuration(remainingTime);
            context->displayManager->refresh();
        }
    }

    storeProcessTimer->update();
}
void RunningState::handleInput(SystemContext* context, InputEvent event) {
    if (event == InputEvent::BackPressed) {
        stateMachine->changeState(AppStates::ABORTING, context);
    }
}



SettingProcessState::SettingProcessState() {
    setupStateMachine.setOnStartEnterCallback(
        [this](SystemContext* context) {

        context->processManager->createCurrentProcess(
            setupPage->GetSetupHumidityMin(),
            setupPage->GetSetupHumidityMax(),
            setupPage->GetSetupTemperatureMin(),
            setupPage->GetSetupTemperatureMax(),
            AppTimeSpan(0, 0, 1, 0), //TODO vents interval
            AppTimeSpan(0, 0, 1, 0), //TODO vents duration
            setupPage->GetDurationSetup(),
            context->timeManager->getCurrentTime(),
            context->actuatorManager);

        if (!context->processManager->storeCurrentProcess()) {
            log("SettingProcessState setOnStartEnterCallback - failed to store newly created process");
        }

        stateMachine->changeState(AppStates::RUNNING, context);
    });
}
void SettingProcessState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::SETUP);
    if (!setupPage) {
        setupPage = context->displayManager->getPageAs<PageAppSetup>(Pages::SETUP);
    }
    setupStateMachine.changeState(SetupStates::HUMIDITY_RANGE_SELECT, context); // init nested setup state machine state to initial state
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
        stateMachine->changeState(AppStates::IDLING, context);
    }
    else { // pass event into nested setup state machine
        setupStateMachine.handleInput(event, context);
        update(context);
    }
}



void StartingUpState::enter(SystemContext* context) {
    /// StateLogic:
    /// initialize all managers in the system context object
    /// if any fails, then transite to SYSTEM_IN_ERROR state.
    if (!context->inputManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_INPUT_MANAGER);
        return;
    }
    if (!context->sensorManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_SENSOR_MANAGER);
        return;
    }
    if (!context->displayManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_DISPLAY_MANAGER);
        return;
    }
    if (!context->actuatorManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_ACTUATOR_MANAGER);
        return;
    }
    if (!context->processManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_PROCESS_MANAGER);
        return;
    }
    if (!context->networkManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_NETWORK_MANAGER);
        return;
    }
    if (!context->timeManager->initialize()) {
        GoToErrorState(context, AppErrors::ERR_INIT_TIME_MANAGER);
        return;
    }

    // attempt to update RTC from NTP service
    if (context->timeManager->UpdateRtcFromNtpService(context->networkManager)) {
        log("update time from ntp service successful");
        log(context->timeManager->getCurrentTime().ToString());
    }
    else {
        log("update time from ntp service failed");
    }

    // transite forward to INITIALIZING state
    stateMachine->changeState(AppStates::INITIALIZING, context);
}
void StartingUpState::exit(SystemContext* context) {}
void StartingUpState::update(SystemContext* context) {}
void StartingUpState::handleInput(SystemContext* context, InputEvent event) {}



void SystemInErrorState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::ERROR);
}
void SystemInErrorState::exit(SystemContext* context) {}
void SystemInErrorState::update(SystemContext* context) {
    context->displayManager->refresh();
}
void SystemInErrorState::handleInput(SystemContext* context, InputEvent event) {}



DiagnosingState::DiagnosingState() {
    diagStateMachine.setOnExitDiagCallback(
        [this](SystemContext* context) {
        stateMachine->changeState(AppStates::IDLING, context);
    });
}
void DiagnosingState::enter(SystemContext* context) {
    context->displayManager->changePage(Pages::DIAG);
    if (!diagPage) {
        diagPage = context->displayManager->getPageAs<PageAppDiag>(Pages::DIAG);
    }
    diagStateMachine.changeState(DiagStates::HumidifiersSelected, context); // init nested diag state machine
}
void DiagnosingState::exit(SystemContext* context) {}
void DiagnosingState::update(SystemContext* context) {
    if (diagPage) {
        float humidity, temperature;
        if (context->sensorManager->getHumidity(humidity))
            diagPage->SetHumidity(humidity);
        if (context->sensorManager->getTemperature(temperature))
            diagPage->SetTemperature(temperature);
        diagPage->SetDateTime(context->timeManager->getCurrentTime());
        context->displayManager->refresh();
    }
}
void DiagnosingState::handleInput(SystemContext* context, InputEvent event) {
    diagStateMachine.handleInput(event, context);
    update(context);
}
