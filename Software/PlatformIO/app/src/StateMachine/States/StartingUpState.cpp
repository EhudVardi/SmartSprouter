#include "StateMachine/States/StartingUpState.h"

void StartingUpState::enter(SystemContext* context) {
    // Initialization logic
    std::cout << "Entering StartingUpState" << std::endl;
}
void StartingUpState::exit(SystemContext* context) {
    std::cout << "Exiting StartingUpState" << std::endl;
}
void StartingUpState::update(SystemContext* context) {
    // Update logic
    std::cout << "Updating StartingUpState" << std::endl;
    
    // Example: Transition to next state when done initializing
    if (true /* some condition */) {
        stateMachine->changeState("InitializingState", context);  // Trigger state transition
    }
}
void StartingUpState::handleInput(SystemContext* context, InputEvent event) {
    // Handle input events
}