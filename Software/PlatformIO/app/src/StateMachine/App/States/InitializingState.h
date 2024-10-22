#ifndef INITIALIZING_STATE_H
#define INITIALIZING_STATE_H

#include "StateMachine/App/State.h"

class InitializingState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // INITIALIZING_STATE_H
