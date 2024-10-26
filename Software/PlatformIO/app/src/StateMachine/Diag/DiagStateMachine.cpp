#include "StateMachine/Diag/DiagStateMachine.h"
#include "StateMachine/Diag/DiagStates.h"
#include <iostream>

DiagStateMachine::DiagStateMachine() {

    auto humidifiersSelected = std::make_shared<H_S>();
    auto humidifiersEdited = std::make_shared<H_E>();

    // Add states to the state machine
    addState(DiagStates::HumidifiersSelected, humidifiersSelected);
    addState(DiagStates::HumidifiersEdited, humidifiersEdited);
}

void DiagStateMachine::setOnExitDiagCallback(std::function<void(SystemContext*)> callback) {
    onExitDiag = callback;
}

void DiagStateMachine::fireOnExitDiagEvent(SystemContext* context) {
    if (onExitDiag) {
        onExitDiag(context);
    }
}
