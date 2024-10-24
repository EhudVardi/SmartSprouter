#ifndef APPLICATION_H
#define APPLICATION_H

#include "SystemContext/SystemContext.h"
#include "StateMachine/App/AppStateMachine.h"
#include "Utils/Timer.h"

class Application {
private:
    SystemContext context;
    AppStateMachine stateMachine;

    Timer inputPollingTimer;
    Timer stateMachineTimer;

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
