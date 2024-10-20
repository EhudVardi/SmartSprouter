#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <memory>
#include <unordered_map>
#include "StateMachine/States/State.h"
#include "SystemContext/SystemContext.h"
#include "StateMachine/StatesEnumeration.h"

class State;

class StateMachine {
private:
    std::shared_ptr<State> currentState;
    std::unordered_map<States, std::shared_ptr<State>> stateMap; // Store states

public:
    StateMachine();
    
    // Function to add states to the state machine
    void addState(States stateEnum, std::shared_ptr<State> state);

    // Change state by name
    void changeState(States stateEnum, SystemContext* context);

    void update(SystemContext* context);
    void handleInput(InputEvent event, SystemContext* context);
};

#endif // STATE_MACHINE_H
