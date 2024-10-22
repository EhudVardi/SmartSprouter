#ifndef SETUP_STATES_ENUMERATION_H
#define SETUP_STATES_ENUMERATION_H

#include <unordered_map>
#include <string>

enum class SetupStates {
    HumidityRangeSelect,
    HumidityRangeEditMin,
    HumidityRangeEditMax,
    TemperatureRangeSelect,
    TemperatureRangeEditMin,
    TemperatureRangeEditMax,
    DurationSelect,
    DurationEdit,
    Start,
};

// Use a static map to convert enums to strings
inline const char* States_ToString(SetupStates s) {
    static const std::unordered_map<SetupStates, const char*> stateMap = {
        { SetupStates::HumidityRangeSelect, "HumidityRangeSelect" },
        { SetupStates::HumidityRangeEditMin, "HumidityRangeEditMin" },
        { SetupStates::HumidityRangeEditMax, "HumidityRangeEditMax" },
        { SetupStates::TemperatureRangeSelect, "TemperatureRangeSelect" },
        { SetupStates::TemperatureRangeEditMin, "TemperatureRangeEditMin" },
        { SetupStates::TemperatureRangeEditMax, "TemperatureRangeEditMax" },
        { SetupStates::DurationSelect, "DurationSelect" },
        { SetupStates::DurationEdit, "DurationEdit" },
        { SetupStates::Start, "Start" },
    };

    auto it = stateMap.find(s);
    return (it != stateMap.end()) ? it->second : "[Unknown State_type]";
}

#endif // SETUP_STATES_ENUMERATION_H