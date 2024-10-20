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
}
void InitializingState::handleInput(SystemContext* context, InputEvent event) {
    // Handle input events
}