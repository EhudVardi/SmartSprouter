#include "DiagState.h"

#ifndef HUMIDIFIERS_SELECTED_STATE_H
#define HUMIDIFIERS_SELECTED_STATE_H

class H_S : public DiagState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // HUMIDIFIERS_SELECTED_STATE_H

#ifndef HUMIDIFIERS_EDIT_STATE_H
#define HUMIDIFIERS_EDIT_STATE_H

class H_E : public DiagState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // HUMIDIFIERS_EDIT_STATE_H
