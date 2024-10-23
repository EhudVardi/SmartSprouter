#ifndef ABORTING_STATE_H
#define ABORTING_STATE_H

#include "StateMachine/App/State.h"

class AbortingState : public AppState {
private:
    std::shared_ptr<PageAppAbort> abortPage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // ABORTING_STATE_H
