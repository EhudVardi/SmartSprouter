#ifndef IDLING_STATE_H
#define IDLING_STATE_H

#include "StateMachine/States/State.h"

class IdlingState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // IDLING_STATE_H
