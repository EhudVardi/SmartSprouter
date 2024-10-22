#ifndef STATE_H
#define STATE_H

#include "StateMachine/StateBase.h"
#include "StateMachine/App/StateMachine.h"
#include <iostream>

class AppStateMachine; // Forward declare AppStateMachine

class AppState : public StateBase<AppStateMachine> {};

#endif // STATE_H
