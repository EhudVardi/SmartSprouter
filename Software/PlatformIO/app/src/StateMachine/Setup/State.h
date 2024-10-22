#ifndef SETUP_STATE_H
#define SETUP_STATE_H

#include "StateMachine/StateBase.h"
#include "StateMachine/Setup/StateMachine.h"
#include <iostream>

class SetupStateMachine; // Forward declare SetupStateMachine

class SetupState : public StateBase<SetupStateMachine> {};

#endif // SETUP_STATE_H
