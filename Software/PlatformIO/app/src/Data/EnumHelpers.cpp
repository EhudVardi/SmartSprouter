#include "Data/EnumHelpers.h"

namespace EnumHelpers {

    EnumHelper<AppStates> AppStatesHelper({
        { AppStates::StartingUp, "StartingUp" },
        { AppStates::SystemInError, "SystemInError" },
        { AppStates::Initializing, "Initializing" },
        { AppStates::Idling, "Idling" },
        { AppStates::Informing, "Informing" },
        { AppStates::SettingProcess, "SettingProcess" },
        { AppStates::Running, "Running" },
        { AppStates::Aborting, "Aborting" },
        { AppStates::Diagnosing, "Diagnosing" }
    }, AppStates::Diagnosing); // last valid state
    
    EnumHelper<SetupStates> SetupStatesHelper({
        { SetupStates::HumidityRangeSelect, "HumidityRangeSelect" },
        { SetupStates::HumidityRangeEditMin, "HumidityRangeEditMin" },
        { SetupStates::HumidityRangeEditMax, "HumidityRangeEditMax" },
        { SetupStates::TemperatureRangeSelect, "TemperatureRangeSelect" },
        { SetupStates::TemperatureRangeEditMin, "TemperatureRangeEditMin" },
        { SetupStates::TemperatureRangeEditMax, "TemperatureRangeEditMax" },
        { SetupStates::DurationSelect, "DurationSelect" },
        { SetupStates::DurationEdit, "DurationEdit" },
        { SetupStates::StartSelect, "StartSelect" }
    }, SetupStates::StartSelect); // last valid state
    
    EnumHelper<HumidifierActions> HumidifierActionsHelper({
        { HumidifierActions::Off, "  Off " },
        { HumidifierActions::Low, "  Low " },
        { HumidifierActions::High, "  High" },
    }, HumidifierActions::High); // last valid state
}