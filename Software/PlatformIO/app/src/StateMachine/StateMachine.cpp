#include "StateMachine/StateMachine.h"
#include "StateMachine/States/StartingUpState.h"
#include "StateMachine/States/InitializingState.h"
#include <iostream>

StateMachine::StateMachine() {
    
    auto startingUpState = std::make_shared<StartingUpState>();
    auto initializingState = std::make_shared<InitializingState>();

    // Add states to the state machine
    addState(States::StartingUp, startingUpState);
    addState(States::Initializing, initializingState);
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
