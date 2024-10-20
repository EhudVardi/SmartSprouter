#include "StateMachine/StateMachine.h"
#include "StateMachine/States/StartingUpState.h"
#include "StateMachine/States/InitializingState.h"
#include "StateMachine/States/SystemInErrorState.h"
#include "StateMachine/States/IdlingState.h"
#include "StateMachine/States/SettingProcessState.h"
#include "StateMachine/States/SettingParamState.h"
#include "StateMachine/States/RunningState.h"
#include "StateMachine/States/AbortingState.h"
#include <iostream>

StateMachine::StateMachine() {
    
    auto startingUpState = std::make_shared<StartingUpState>();
    auto initializingState = std::make_shared<InitializingState>();
    auto systemInErrorState = std::make_shared<SystemInErrorState>();
    auto idlingState = std::make_shared<IdlingState>();
    auto settingProcessState = std::make_shared<SettingProcessState>();
    auto settingParamState = std::make_shared<SettingParamState>();
    auto runningState = std::make_shared<RunningState>();
    auto abortingState = std::make_shared<AbortingState>();

    // Add states to the state machine
    addState(States::StartingUp, startingUpState);
    addState(States::Initializing, initializingState);
    addState(States::SystemInError, systemInErrorState);
    addState(States::Idling, idlingState);
    addState(States::SettingProcess, settingProcessState);
    addState(States::SettingParam, settingParamState);
    addState(States::Running, runningState);
    addState(States::Aborting, abortingState);
}

void StateMachine::addState(States stateEnum, std::shared_ptr<State> state) {
    stateMap[stateEnum] = state;
    state->setStateMachine(this);
}

void StateMachine::changeState(States stateEnum, SystemContext* context) {
    auto newState = stateMap.find(stateEnum);
    if (newState != stateMap.end()) {
        if (currentState) {
            currentState->exit(context);
        }
        currentState = newState->second;
        if (currentState) {
            currentState->enter(context);
        }
    } else {
        std::cerr << "State " << States_ToString(stateEnum) << " not found!" << std::endl;
    }
}

void StateMachine::update(SystemContext* context) {
    if (currentState) {
        currentState->update(context);
    }
}

void StateMachine::handleInput(InputEvent event, SystemContext* context) {
    if (currentState) {
        currentState->handleInput(context, event);
    }
}
