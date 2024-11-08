#ifndef SETUP_STATE_MACHINE_H
#define SETUP_STATE_MACHINE_H

#include "StateMachine/StateMachineBase.h"
#include "SetupState.h"
#include "SetupStatesEnum.h"

#include <iostream>
#include <functional>

class SetupState;

class SetupStateMachine : public StateMachineBase<SetupState, SetupStates> {
private:
  std::function<void(SystemContext*)> onStartEnter; // event that fires when the Start Setup state gets Enter input
  
public: 
    SetupStateMachine();

    void setOnStartEnterCallback(std::function<void(SystemContext*)> callback);
    void fireOnStartEnterEvent(SystemContext* context);
};

#endif // SETUP_STATE_MACHINE_H
