#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "StateMachine/App/State.h"
#include "StateMachine/App/StatesEnumeration.h"

#include <iostream>

class AppState;

class AppStateMachine : public StateMachineBase<AppState, AppStates> {
public: 
    AppStateMachine();
};

#endif // STATE_MACHINE_H
