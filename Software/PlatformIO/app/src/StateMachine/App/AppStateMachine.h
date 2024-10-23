#ifndef APP_STATE_MACHINE_H
#define APP_STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "StateMachine/App/AppState.h"
#include "StateMachine/App/AppStatesEnum.h"

#include <iostream>

class AppState;

class AppStateMachine : public StateMachineBase<AppState, AppStates> {
public: 
    AppStateMachine();
};

#endif // APP_STATE_MACHINE_H
