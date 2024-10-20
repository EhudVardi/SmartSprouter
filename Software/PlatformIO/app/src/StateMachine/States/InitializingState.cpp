#include "StateMachine/States/InitializingState.h"

void InitializingState::enter(SystemContext* context) {
    // Initialization logic
    std::cout << "Entering InitializingState" << std::endl;
}
void InitializingState::exit(SystemContext* context) {
    std::cout << "Exiting InitializingState" << std::endl;
}
void InitializingState::update(SystemContext* context) {
    // Update logic
    std::cout << "Updating InitializingState" << std::endl;
    
    // Example: Transition to next state when done initializing
    if (true /* some condition */) {
        stateMachine->changeState("StartingUpState", context);  // Trigger state transition
    }
}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {
    // Handle input events
}