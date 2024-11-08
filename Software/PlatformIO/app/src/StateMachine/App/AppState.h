#ifndef APPSTATE_H
#define APPSTATE_H

#include "StateMachine/StateBase.h"
#include "AppStateMachine.h"
#include <iostream>

class AppStateMachine; // Forward declare AppStateMachine

class AppState : public StateBase<AppStateMachine> {
private:
    std::shared_ptr<PageAppError> errorPage = nullptr;
public:
    void GoToErrorState(SystemContext* context, AppErrors error, const String& errParams = "no params");
};

#endif // APPSTATE_H
