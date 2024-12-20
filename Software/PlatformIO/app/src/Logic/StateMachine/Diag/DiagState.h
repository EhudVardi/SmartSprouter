#ifndef DIAGNOSTICS_STATE_H
#define DIAGNOSTICS_STATE_H

#include "Logic/StateMachine/StateBase.h"
#include "DiagStateMachine.h"

class DiagStateMachine; // Forward declare SetupStateMachine

class DiagState : public StateBase<DiagStateMachine> {
protected:
    std::shared_ptr<PageAppDiag> diagPage = nullptr;

public:
    void enter(SystemContext* context) override {
        if (!diagPage) {
            diagPage = context->displayManager->getPageAs<PageAppDiag>(Pages::DIAG);
        }
    }
};

#endif // DIAGNOSTICS_STATE_H
