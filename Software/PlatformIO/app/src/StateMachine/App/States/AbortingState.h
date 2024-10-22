#ifndef ABORTING_STATE_H
#define ABORTING_STATE_H

#include "StateMachine/States/State.h"

class AbortingState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // ABORTING_STATE_H
