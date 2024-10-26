#ifndef DIAGNOSTICS_STATE_H
#define DIAGNOSTICS_STATE_H

#include "StateMachine/StateBase.h"
#include "StateMachine/Diag/DiagStateMachine.h"
#include <iostream>

class DiagStateMachine; // Forward declare SetupStateMachine

class DiagState : public StateBase<DiagStateMachine> {
protected:
    std::shared_ptr<PageAppDiag> diagPage = nullptr;

public:
    void enter(SystemContext* context) override {
        if (!diagPage) {
            diagPage = context->displayManager->getPageAs<PageAppDiag>(Pages::Diag);
        }
    }
};

#endif // DIAGNOSTICS_STATE_H
