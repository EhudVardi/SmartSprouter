#ifndef SETUP_STATES_ENUMERATION_H
#define SETUP_STATES_ENUMERATION_H

#include <unordered_map>
#include <string>

enum class SetupStates {
    StartingUp,
    SystemInError,
    Initializing,
    Idling,
    Informing,
    SettingProcess,
    Running,
    Aborting,
};

// Use a static map to convert enums to strings
inline const char* States_ToString(SetupStates s) {
    static const std::unordered_map<SetupStates, const char*> stateMap = {
        { SetupStates::StartingUp, "StartingUp" },
        { SetupStates::SystemInError, "SystemInError" },
        { SetupStates::Initializing, "Initializing" },
        { SetupStates::Idling, "Idling" },
        { SetupStates::Informing, "Informing" },
        { SetupStates::SettingProcess, "SettingProcess" },
        { SetupStates::Running, "Running" },
        { SetupStates::Aborting, "Aborting" }
    };

    auto it = stateMap.find(s);
    return (it != stateMap.end()) ? it->second : "[Unknown State_type]";
}

#endif // SETUP_STATES_ENUMERATION_H