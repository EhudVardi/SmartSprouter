#ifndef STATE_H
#define STATE_H

#include "SystemContext/SystemContext.h"
#include "StateMachine/StateMachine.h"
#include <iostream>

class StateMachine; // Forward declare StateMachine

class State {
protected:
    StateMachine* stateMachine; // Each state has a reference to the state machine

public:
    virtual ~State() = default;

    // Constructor that injects the state machine
    void setStateMachine(StateMachine* machine) {
        this->stateMachine = machine;
    }

    virtual void enter(SystemContext* context) = 0;
    virtual void exit(SystemContext* context) = 0;
    virtual void update(SystemContext* context) = 0;
    virtual void handleInput(SystemContext* context, InputEvent event) = 0;
};

#endif // STATE_H
