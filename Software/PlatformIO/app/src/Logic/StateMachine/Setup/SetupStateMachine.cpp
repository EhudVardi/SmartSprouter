#include "SetupStateMachine.h"
#include "SetupStates.h"

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

    addState(SetupStates::HUMIDITY_RANGE_SELECT, HumidityRangeSelect);
    addState(SetupStates::HUMIDITY_RANGE_EDIT_MIN, HumidityRangeEditMin);
    addState(SetupStates::HUMIDITY_RANGE_EDIT_MAX, HumidityRangeEditMax);
    addState(SetupStates::TEMPERATURE_RANGE_SELECT, TemperatureRangeSelect);
    addState(SetupStates::TEMPERATURE_RANGE_EDIT_MIN, TemperatureRangeEditMin);
    addState(SetupStates::TEMPERATURE_RANGE_EDIT_MAX, TemperatureRangeEditMax);
    addState(SetupStates::DURATION_SELECT, DurationSelect);
    addState(SetupStates::DURATION_EDIT, DurationEdit);
    addState(SetupStates::START_SELECT, StartSelect);
}

void SetupStateMachine::setOnStartEnterCallback(std::function<void(SystemContext*)> callback) {
    onStartEnter = callback;
}

void SetupStateMachine::fireOnStartEnterEvent(SystemContext* context) {
    if (onStartEnter) {
        onStartEnter(context);
    }
}
