#ifndef STARTING_UP_STATE_H
#define STARTING_UP_STATE_H

#include "StateMachine/App/State.h"

class StartingUpState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // STARTING_UP_STATE_H
