#ifndef APPLICATION_H
#define APPLICATION_H

#include "SystemContext/SystemContext.h"
#include "Logic/StateMachine/App/AppStateMachine.h"
#include "Utils/Timer.h"

class Application {
private:
    SystemContext context;
    AppStateMachine stateMachine;

    Timer inputPollingTimer;
    Timer stateMachineTimer;
    Timer timePollingTimer;

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
