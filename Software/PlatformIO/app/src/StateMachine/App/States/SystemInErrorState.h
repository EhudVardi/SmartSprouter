#ifndef SYSTEM_IN_ERROR_STATE_H
#define SYSTEM_IN_ERROR_STATE_H

#include "StateMachine/States/State.h"

class SystemInErrorState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // SYSTEM_IN_ERROR_STATE_H
