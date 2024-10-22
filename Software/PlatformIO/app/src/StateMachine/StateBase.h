// StateBase.h
#ifndef STATE_BASE_H
#define STATE_BASE_H

#include "SystemContext/SystemContext.h"

template<typename TStateMachine>
class StateBase {
protected:
    TStateMachine* stateMachine; // Each state has a reference to its specific state machine type

public:
    using TStateMachineType = TStateMachine; // Allow referring to this type in derived classes

    virtual ~StateBase() = default;

    void setStateMachine(TStateMachine* machine) {
        this->stateMachine = machine;
    }

    virtual void enter(SystemContext* context) = 0;
    virtual void exit(SystemContext* context) = 0;
    virtual void update(SystemContext* context) = 0;
    virtual void handleInput(SystemContext* context, InputEvent event) = 0;
};

#endif // STATE_BASE_H
