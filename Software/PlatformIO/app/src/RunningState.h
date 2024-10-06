#ifndef RUNNING_STATE_H
#define RUNNING_STATE_H

#include "State.h"

class RunningState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // RUNNING_STATE_H
