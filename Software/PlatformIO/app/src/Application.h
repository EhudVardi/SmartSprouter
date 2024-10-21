#ifndef APPLICATION_H
#define APPLICATION_H

#include "SystemContext/SystemContext.h"
#include "StateMachine/StateMachine.h"
#include "Timer.h"

class Application {
private:
    SystemContext context;
    StateMachine stateMachine;

    Timer inputPollingTimer;
    Timer stateMachineTimer;

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
