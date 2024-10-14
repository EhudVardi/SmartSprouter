#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <memory>
#include "StateMachine/States/State.h"

class StateMachine {
private:
    std::shared_ptr<State> currentState;

public:
    void changeState(std::shared_ptr<State> newState, SystemContext* context);
    void update(SystemContext* context);
    void handleInput(InputEvent event, SystemContext* context);
};

#endif // STATE_MACHINE_H
