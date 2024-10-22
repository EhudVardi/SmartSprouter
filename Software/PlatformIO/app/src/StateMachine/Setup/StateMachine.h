#ifndef SETUP_STATE_MACHINE_H
#define SETUP_STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "StateMachine/Setup/State.h"
#include "StateMachine/Setup/StatesEnumeration.h"

#include <iostream>

class SetupState;

class SetupStateMachine : public StateMachineBase<SetupState, SetupStates> {
public: 
    SetupStateMachine();
};

#endif // SETUP_STATE_MACHINE_H
