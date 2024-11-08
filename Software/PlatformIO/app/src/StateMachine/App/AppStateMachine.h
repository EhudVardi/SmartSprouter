#ifndef APP_STATE_MACHINE_H
#define APP_STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "AppState.h"
#include "AppStatesEnum.h"

class AppState;

class AppStateMachine : public StateMachineBase<AppState, AppStates> {
public: 
    AppStateMachine();
};

#endif // APP_STATE_MACHINE_H
