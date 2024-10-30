#include "StateMachine/App/AppState.h"

void AppState::GoToErrorState(SystemContext* context, AppErrors error, const String& errParams) {
    if (!errorPage) {
        errorPage = context->displayManager->getPageAs<PageAppError>(Pages::Error);
        errorPage->SetError(error, errParams);
    }
    stateMachine->changeState(AppStates::SystemInError, context);
}

