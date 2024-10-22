#ifndef SETTING_PROCESS_STATE_H
#define SETTING_PROCESS_STATE_H

#include "StateMachine/App/State.h"

class SettingProcessState : public AppState {
private:
    std::shared_ptr<PageAppIdle> setupPage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // SETTING_PROCESS_STATE_H
