#include "StateMachine/StateMachine.h"
#include "StateMachine/States/StartingUpState.h"
#include "StateMachine/States/InitializingState.h"
#include <iostream>

StateMachine::StateMachine() {
    
    auto startingUpState = std::make_shared<StartingUpState>();
    auto initializingState = std::make_shared<InitializingState>();

    // Add states to the state machine
    addState("StartingUpState", startingUpState);
    addState("InitializingState", initializingState);
}

void StateMachine::addState(const std::string& stateName, std::shared_ptr<State> state) {
    stateMap[stateName] = state;
    state->setStateMachine(this);
}

void StateMachine::changeState(const std::string& stateName, SystemContext* context) {
    auto newState = stateMap.find(stateName);
    if (newState != stateMap.end()) {
        if (currentState) {
            currentState->exit(context);
        }
        currentState = newState->second;
        if (currentState) {
            currentState->enter(context);
        }
    } else {
        std::cerr << "State " << stateName << " not found!" << std::endl;
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
