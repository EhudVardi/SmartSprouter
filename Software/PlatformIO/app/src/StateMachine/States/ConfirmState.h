#ifndef CONFIRM_STATE_H
#define CONFIRM_STATE_H

#include "StateMachine/States/State.h"

class ConfirmState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // CONFIRM_STATE_H
