#ifndef SETTING_PARAM_STATE_H
#define SETTING_PARAM_STATE_H

#include "StateMachine/States/State.h"

class SettingParamState : public State {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // SETTING_PARAM_STATE_H
