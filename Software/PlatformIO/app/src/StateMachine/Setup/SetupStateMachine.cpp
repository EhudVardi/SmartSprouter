#include "StateMachine/Setup/SetupStateMachine.h"
#include "StateMachine/Setup/SetupStates.h"
#include <iostream>

SetupStateMachine::SetupStateMachine() {

    auto HumidityRangeSelect = std::make_shared<HR_S>();
    auto HumidityRangeEditMin = std::make_shared<HR_E_MIN>();
    auto HumidityRangeEditMax = std::make_shared<HR_E_MAX>();
    auto TemperatureRangeSelect = std::make_shared<TR_S>();
    auto TemperatureRangeEditMin = std::make_shared<TR_E_MIN>();
    auto TemperatureRangeEditMax = std::make_shared<TR_E_MAX>();
    auto DurationSelect = std::make_shared<D_S>();
    auto DurationEdit = std::make_shared<D_E>();
    auto StartSelect = std::make_shared<S_S>();

    // Add states to the state machine
    addState(SetupStates::HumidityRangeSelect, HumidityRangeSelect);
    addState(SetupStates::HumidityRangeEditMin, HumidityRangeEditMin);
    addState(SetupStates::HumidityRangeEditMax, HumidityRangeEditMax);
    addState(SetupStates::TemperatureRangeSelect, TemperatureRangeSelect);
    addState(SetupStates::TemperatureRangeEditMin, TemperatureRangeEditMin);
    addState(SetupStates::TemperatureRangeEditMax, TemperatureRangeEditMax);
    addState(SetupStates::DurationSelect, DurationSelect);
    addState(SetupStates::DurationEdit, DurationEdit);
    addState(SetupStates::StartSelect, StartSelect);
}

void SetupStateMachine::setOnStartEnterCallback(std::function<void(SystemContext*)> callback) {
    onStartEnter = callback;
}

void SetupStateMachine::fireOnStartEnterEvent(SystemContext* context) {
    if (onStartEnter) {
        onStartEnter(context);
    }
}
