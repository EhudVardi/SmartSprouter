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
    addState(AppStates::STARTING_UP, startingUpState);
    addState(AppStates::INITIALIZING, initializingState);
    addState(AppStates::SYSTEM_IN_ERROR, systemInErrorState);
    addState(AppStates::IDLING, idlingState);
    addState(AppStates::INFORMING, informingState);
    addState(AppStates::SETTING_PROCESS, settingProcessState);
    addState(AppStates::RUNNING, runningState);
    addState(AppStates::ABORTING, abortingState);
    addState(AppStates::DIAGNOSING, diagnosingState);
}
