#ifndef DIAG_STATE_MACHINE_H
#define DIAG_STATE_MACHINE_H

#include <functional>
#include "StateMachine/StateMachineBase.h"
#include "DiagState.h"
#include "DiagStatesEnum.h"

class DiagState;

class DiagStateMachine : public StateMachineBase<DiagState, DiagStates> {
private:
  std::function<void(SystemContext*)> onExitDiag; // event that fires when the Start SETUP state gets Enter input
  
public: 
    DiagStateMachine();

    void setOnExitDiagCallback(std::function<void(SystemContext*)> callback);
    void fireOnExitDiagEvent(SystemContext* context);
};

#endif // DIAG_STATE_MACHINE_H
