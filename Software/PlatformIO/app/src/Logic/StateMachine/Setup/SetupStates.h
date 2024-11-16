#include "SetupState.h"

#ifndef HUMIDITY_RANGE_SELECTED_STATE_H
#define HUMIDITY_RANGE_SELECTED_STATE_H

class HR_S : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // HUMIDITY_RANGE_SELECTED_STATE_H

#ifndef HUMIDITY_RANGE_EDIT_MIN_STATE_H
#define HUMIDITY_RANGE_EDIT_MIN_STATE_H

class HR_E_MIN : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // HUMIDITY_RANGE_EDIT_MIN_STATE_H

#ifndef HUMIDITY_RANGE_EDIT_MAX_STATE_H
#define HUMIDITY_RANGE_EDIT_MAX_STATE_H

class HR_E_MAX : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // HUMIDITY_RANGE_EDIT_MIN_STATE_H

#ifndef TEMPERATURE_RANGE_SELECTED_STATE_H
#define TEMPERATURE_RANGE_SELECTED_STATE_H

class TR_S : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // TEMPERATURE_RANGE_SELECTED_STATE_H

#ifndef TEMPERATURE_RANGE_EDIT_MIN_STATE_H
#define TEMPERATURE_RANGE_EDIT_MIN_STATE_H

class TR_E_MIN : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // TEMPERATURE_RANGE_EDIT_MIN_STATE_H

#ifndef TEMPERATURE_RANGE_EDIT_MAX_STATE_H
#define TEMPERATURE_RANGE_EDIT_MAX_STATE_H

class TR_E_MAX : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // TEMPERATURE_RANGE_EDIT_MIN_STATE_H

#ifndef DURATION_SELECTED_STATE_H
#define DURATION_SELECTED_STATE_H

class D_S : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // DURATION_SELECTED_STATE_H

#ifndef DURATION_EDIT_STATE_H
#define DURATION_EDIT_STATE_H

class D_E : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // DURATION_EDIT_STATE_H

#ifndef START_SELECTED_STATE_H
#define START_SELECTED_STATE_H

class S_S : public SetupState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // START_SELECTED_STATE_H
