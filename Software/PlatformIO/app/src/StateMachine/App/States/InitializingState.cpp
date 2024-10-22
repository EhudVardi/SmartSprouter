#include "StateMachine/App/States/InitializingState.h"

void InitializingState::enter(SystemContext* context) {
    /// StateLogic:
    /// <TODO> check in memory if an unfinished process exists
    /// <TODO> if exist then load it into current process and transition into running state
    /// otherwise, transition into idle state
    stateMachine->changeState(States::Idling, context);
}
void InitializingState::exit(SystemContext* context) {}
void InitializingState::update(SystemContext* context) {}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {}