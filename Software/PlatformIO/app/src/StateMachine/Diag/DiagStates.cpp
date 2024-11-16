#include "DiagStates.h"

void H_S::enter(SystemContext* context) { 
    DiagState::enter(context);
    if (diagPage) diagPage->SetHumidifiersEditState(NamedValueEditState::Selected);
}
void H_S::exit(SystemContext* context) { }
void H_S::update(SystemContext* context) { }
void H_S::handleInput(SystemContext* context, InputEvent event) {
    if (diagPage) {
        switch (event) {
            case InputEvent::EnterPressed: stateMachine->changeState(DiagStates::HumidifiersEdited, context); break;
            case InputEvent::RotatedRight: /*TODO: jump to next actuator selector state */ break;
            case InputEvent::RotatedLeft: /*TODO: jump to previous actuator selector state */ break;
            case InputEvent::BackPressed: stateMachine->fireOnExitDiagEvent(context); break;
            default: break;
        }
    }
}

void H_E::enter(SystemContext* context) { 
    DiagState::enter(context);
    if (diagPage) diagPage->SetHumidifiersEditState(NamedValueEditState::Entered);
}
void H_E::exit(SystemContext* context) { }
void H_E::update(SystemContext* context) { }
void H_E::handleInput(SystemContext* context, InputEvent event) {
    if (diagPage) {
        switch (event) {
            case InputEvent::EnterPressed: context->actuatorManager->SetHumidifiers(diagPage->GetSelectedHumidifierAction()); break;
            case InputEvent::RotatedRight: diagPage->SelectNextHumidifierAction(); break;
            case InputEvent::RotatedLeft: diagPage->SelectPrevHumidifierAction(); break;
            case InputEvent::BackPressed: stateMachine->changeState(DiagStates::HumidifiersSelected, context); break;
            default: break;
        }
    }
}
