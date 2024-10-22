#ifndef IDLING_STATE_H
#define IDLING_STATE_H

#include "StateMachine/App/State.h"

class IdlingState : public State {
private:
    std::shared_ptr<PageAppIdle> idlePage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // IDLING_STATE_H
