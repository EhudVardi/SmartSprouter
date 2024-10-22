#include "StateMachine/App/States/StartingUpState.h"

void StartingUpState::enter(SystemContext* context) {
    /// StateLogic:
    /// initialize all managers in the system context object
    /// if any fails, then transite to SystemInError state. else transite forward to Initializing state
    if (!context->inputManager->initialize()) {
        stateMachine->changeState(States::SystemInError, context);
        return;
    }
    if (!context->sensorManager->initialize()) {
        stateMachine->changeState(States::SystemInError, context);
        return;
    }
    if (!context->displayManager->initialize()) {
        stateMachine->changeState(States::SystemInError, context);
        return;
    }
    if (!context->actuatorManager->initialize()) {
        stateMachine->changeState(States::SystemInError, context);
        return;
    }
    if (!context->processManager->initialize()) {
        stateMachine->changeState(States::SystemInError, context);
        return;
    }
    stateMachine->changeState(States::Initializing, context);
}

void StartingUpState::exit(SystemContext* context) { }
void StartingUpState::update(SystemContext* context) { }
void StartingUpState::handleInput(SystemContext* context, InputEvent event) { }