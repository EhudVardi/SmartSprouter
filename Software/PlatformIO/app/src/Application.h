#ifndef APPLICATION_H
#define APPLICATION_H

#include "SystemContext.h"
#include "StateMachine.h"

class Application {
private:
    SystemContext context;
    StateMachine stateMachine;

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
