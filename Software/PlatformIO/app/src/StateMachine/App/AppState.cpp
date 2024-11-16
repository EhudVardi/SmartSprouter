#include "AppState.h"

void AppState::GoToErrorState(SystemContext* context, AppErrors error, const String& errParams) {
    if (!errorPage) {
        errorPage = context->displayManager->getPageAs<PageAppError>(Pages::ERROR);
        errorPage->SetError(error, errParams);
    }
    stateMachine->changeState(AppStates::SYSTEM_IN_ERROR, context);
}

