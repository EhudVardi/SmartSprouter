#include "AppStateMachine.h"
#include "AppStates.h"

AppStateMachine::AppStateMachine() {
    
    auto startingUpState = std::make_shared<StartingUpState>();
    auto initializingState = std::make_shared<InitializingState>();
    auto systemInErrorState = std::make_shared<SystemInErrorState>();
    auto idlingState = std::make_shared<IdlingState>();
    auto informingState = std::make_shared<InformingState>();
    auto settingProcessState = std::make_shared<SettingProcessState>();
    auto runningState = std::make_shared<RunningState>();
    auto abortingState = std::make_shared<AbortingState>();
    auto diagnosingState = std::make_shared<DiagnosingState>();

    // Add states to the state machine
    addState(AppStates::StartingUp, startingUpState);
    addState(AppStates::Initializing, initializingState);
    addState(AppStates::SystemInError, systemInErrorState);
    addState(AppStates::Idling, idlingState);
    addState(AppStates::Informing, informingState);
    addState(AppStates::SettingProcess, settingProcessState);
    addState(AppStates::Running, runningState);
    addState(AppStates::Aborting, abortingState);
    addState(AppStates::Diagnosing, diagnosingState);
}
