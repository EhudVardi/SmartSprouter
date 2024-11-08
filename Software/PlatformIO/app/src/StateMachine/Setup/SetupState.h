#ifndef SETUP_STATE_H
#define SETUP_STATE_H

#include "StateMachine/StateBase.h"
#include "SetupStateMachine.h"

class SetupStateMachine; // Forward declare SetupStateMachine

class SetupState : public StateBase<SetupStateMachine> {
protected:
    std::shared_ptr<PageAppSetup> setupPage = nullptr;

public:
    void enter(SystemContext* context) override {
        if (!setupPage) {
            setupPage = context->displayManager->getPageAs<PageAppSetup>(Pages::Setup);
        }
    }
};

#endif // SETUP_STATE_H
