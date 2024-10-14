#include "StateMachine/StateMachine.h"
#include <iostream>

void StateMachine::changeState(std::shared_ptr<State> newState, SystemContext* context) {
    if (currentState) {
        currentState->exit(context);
    }
    currentState = newState;
    if (currentState) {
        currentState->enter(context);
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
