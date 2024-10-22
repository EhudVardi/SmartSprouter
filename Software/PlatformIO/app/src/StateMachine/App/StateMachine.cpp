#include "StateMachine/App/StateMachine.h"
#include "StateMachine/App/States/StartingUpState.h"
#include "StateMachine/App/States/InitializingState.h"
#include "StateMachine/App/States/SystemInErrorState.h"
#include "StateMachine/App/States/IdlingState.h"
#include "StateMachine/App/States/InformingState.h"
#include "StateMachine/App/States/SettingProcessState.h"
#include "StateMachine/App/States/RunningState.h"
#include "StateMachine/App/States/AbortingState.h"
#include <iostream>

AppStateMachine::AppStateMachine() {
    
    auto startingUpState = std::make_shared<StartingUpState>();
    auto initializingState = std::make_shared<InitializingState>();
    auto systemInErrorState = std::make_shared<SystemInErrorState>();
    auto idlingState = std::make_shared<IdlingState>();
    auto informingState = std::make_shared<InformingState>();
    auto settingProcessState = std::make_shared<SettingProcessState>();
    auto runningState = std::make_shared<RunningState>();
    auto abortingState = std::make_shared<AbortingState>();

    // Add states to the state machine
    addState(AppStates::StartingUp, startingUpState);
    addState(AppStates::Initializing, initializingState);
    addState(AppStates::SystemInError, systemInErrorState);
    addState(AppStates::Idling, idlingState);
    addState(AppStates::Informing, informingState);
    addState(AppStates::SettingProcess, settingProcessState);
    addState(AppStates::Running, runningState);
    addState(AppStates::Aborting, abortingState);
}
