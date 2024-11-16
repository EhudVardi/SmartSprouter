#ifndef APPSTATE_H
#define APPSTATE_H

#include "Logic/StateMachine/StateBase.h"
#include "AppStateMachine.h"

class AppStateMachine; // Forward declare AppStateMachine

class AppState : public StateBase<AppStateMachine> {
private:
    std::shared_ptr<PageAppError> errorPage = nullptr;
public:
    void GoToErrorState(SystemContext* context, AppErrors error, const String& errParams = "no params");
};

#endif // APPSTATE_H
