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
    StartSelect,
};

#endif // SETUP_STATES_ENUMERATION_H