#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "StateMachine/App/State.h"
#include "StateMachine/App/StatesEnumeration.h"

#include <iostream>

class State;

class StateMachine : public StateMachineBase<State, States> {
public: 
    StateMachine();
};

#endif // STATE_MACHINE_H
