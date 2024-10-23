#ifndef RUNNING_STATE_H
#define RUNNING_STATE_H

#include "StateMachine/App/State.h"

class RunningState : public AppState {
private:
    std::shared_ptr<PageAppRun> runPage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // RUNNING_STATE_H
