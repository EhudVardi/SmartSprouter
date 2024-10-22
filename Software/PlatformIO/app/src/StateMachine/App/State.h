#ifndef STATE_H
#define STATE_H

#include "StateMachine/StateBase.h"
#include "StateMachine/App/StateMachine.h"
#include <iostream>

class StateMachine; // Forward declare StateMachine

class State : public StateBase<StateMachine> {};

#endif // STATE_H
