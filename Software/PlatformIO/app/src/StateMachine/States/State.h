#ifndef STATE_H
#define STATE_H

#include "SystemContext/SystemContext.h"

class State {
public:
    virtual void enter(SystemContext* context) = 0;
    virtual void exit(SystemContext* context) = 0;
    virtual void update(SystemContext* context) = 0;
    virtual void handleInput(SystemContext* context, InputEvent event) = 0;
};

#endif // STATE_H
