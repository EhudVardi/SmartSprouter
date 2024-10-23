#ifndef APP_STATES_ENUMERATION_H
#define APP_STATES_ENUMERATION_H

#include <unordered_map>
#include <string>

enum class AppStates {
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
inline const char* States_ToString(AppStates s) {
    static const std::unordered_map<AppStates, const char*> stateMap = {
        { AppStates::StartingUp, "StartingUp" },
        { AppStates::SystemInError, "SystemInError" },
        { AppStates::Initializing, "Initializing" },
        { AppStates::Idling, "Idling" },
        { AppStates::Informing, "Informing" },
        { AppStates::SettingProcess, "SettingProcess" },
        { AppStates::Running, "Running" },
        { AppStates::Aborting, "Aborting" }
    };

    auto it = stateMap.find(s);
    return (it != stateMap.end()) ? it->second : "[Unknown State_type]";
}

#endif // APP_STATES_ENUMERATION_H
