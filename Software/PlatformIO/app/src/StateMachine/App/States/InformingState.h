#ifndef INFORMAING_STATE_H
#define INFORMAING_STATE_H

#include "StateMachine/App/State.h"

class InformingState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // INFORMAING_STATE_H
