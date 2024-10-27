#include "StateMachine/Diag/DiagStates.h"
#include <iostream>

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

// void HR_E_MIN::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetHumidityRangeSelectionMode(NamedRangeEditState::EnteredMin);
// }
// void HR_E_MIN::exit(SystemContext* context) { }
// void HR_E_MIN::update(SystemContext* context) { }
// void HR_E_MIN::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::HumidityRangeEditMax, context); break;
//             case InputEvent::RotatedLeft: setupPage->DecreaseHumidityMin(); break;
//             case InputEvent::RotatedRight: setupPage->IncreaseHumidityMin(); break;
//             default: break;
//         }
//     }
// }

// void HR_E_MAX::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetHumidityRangeSelectionMode(NamedRangeEditState::EnteredMax);
// }
// void HR_E_MAX::exit(SystemContext* context) { }
// void HR_E_MAX::update(SystemContext* context) { }
// void HR_E_MAX::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::HumidityRangeSelect, context); break;
//             case InputEvent::RotatedLeft: setupPage->DecreaseHumidityMax(); break;
//             case InputEvent::RotatedRight: setupPage->IncreaseHumidityMax(); break;
//             default: break;
//         }
//     }
// }

// void TR_S::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetTemperatureRangeSelectionMode(NamedRangeEditState::Selected);
// }
// void TR_S::exit(SystemContext* context) { }
// void TR_S::update(SystemContext* context) { }
// void TR_S::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::TemperatureRangeEditMin, context); break;
//             case InputEvent::RotatedLeft: 
//                 setupPage->SetTemperatureRangeSelectionMode(NamedRangeEditState::None);
//                 stateMachine->changeState(SetupStates::HumidityRangeSelect, context);
//                 break;
//             case InputEvent::RotatedRight: 
//                 setupPage->SetTemperatureRangeSelectionMode(NamedRangeEditState::None);
//                 stateMachine->changeState(SetupStates::DurationSelect, context); 
//                 break;
//             default: break;
//         }
//     }
// }

// void TR_E_MIN::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetTemperatureRangeSelectionMode(NamedRangeEditState::EnteredMin);
// }
// void TR_E_MIN::exit(SystemContext* context) { }
// void TR_E_MIN::update(SystemContext* context) { }
// void TR_E_MIN::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::TemperatureRangeEditMax, context); break;
//             case InputEvent::RotatedLeft: setupPage->DecreaseTemperatureMin(); break;
//             case InputEvent::RotatedRight: setupPage->IncreaseTemperatureMin(); break;
//             default: break;
//         }
//     }
// }

// void TR_E_MAX::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetTemperatureRangeSelectionMode(NamedRangeEditState::EnteredMax);
// }
// void TR_E_MAX::exit(SystemContext* context) { }
// void TR_E_MAX::update(SystemContext* context) { }
// void TR_E_MAX::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::TemperatureRangeSelect, context); break;
//             case InputEvent::RotatedLeft: setupPage->DecreaseTemperatureMax(); break;
//             case InputEvent::RotatedRight: setupPage->IncreaseTemperatureMax(); break;
//             default: break;
//         }
//     }
// }

// void D_S::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetDurationSelectionMode(NamedValueEditState::Selected);
// }
// void D_S::exit(SystemContext* context) { }
// void D_S::update(SystemContext* context) { }
// void D_S::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::DurationEdit, context); break;
//             case InputEvent::RotatedLeft: 
//                 setupPage->SetDurationSelectionMode(NamedValueEditState::None);
//                 stateMachine->changeState(SetupStates::TemperatureRangeSelect, context);
//                 break;
//             case InputEvent::RotatedRight: 
//                 setupPage->SetDurationSelectionMode(NamedValueEditState::None);
//                 stateMachine->changeState(SetupStates::StartSelect, context);
//                 break;
//             default: break;
//         }
//     }
// }

// void D_E::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetDurationSelectionMode(NamedValueEditState::Entered);
// }
// void D_E::exit(SystemContext* context) { }
// void D_E::update(SystemContext* context) { }
// void D_E::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->changeState(SetupStates::DurationSelect, context); break;
//             case InputEvent::RotatedLeft: setupPage->DecreaseDurationDays(); break;
//             case InputEvent::RotatedRight: setupPage->IncreaseDurationDays(); break;
//             default: break;
//         }
//     }
// }

// void S_S::enter(SystemContext* context) { 
//     SetupState::enter(context);
//     if (setupPage) setupPage->SetStartSelectionMode(true);
// }
// void S_S::exit(SystemContext* context) { }
// void S_S::update(SystemContext* context) { }
// void S_S::handleInput(SystemContext* context, InputEvent event) {
//     if (setupPage) {
//         switch (event) {
//             case InputEvent::EnterPressed: stateMachine->fireOnStartEnterEvent(context);
//             case InputEvent::RotatedLeft: 
//                 setupPage->SetStartSelectionMode(false);
//                 stateMachine->changeState(SetupStates::DurationSelect, context);
//                 break;
//             default: break;
//         }
//     }
// }
