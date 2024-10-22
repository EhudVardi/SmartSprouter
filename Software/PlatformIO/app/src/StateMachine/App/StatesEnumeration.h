#ifndef STATES_ENUMERATION_H
#define STATES_ENUMERATION_H

#include <unordered_map>
#include <string>

enum class States {
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
inline const char* States_ToString(States s) {
    static const std::unordered_map<States, const char*> stateMap = {
        { States::StartingUp, "StartingUp" },
        { States::SystemInError, "SystemInError" },
        { States::Initializing, "Initializing" },
        { States::Idling, "Idling" },
        { States::Informing, "Informing" },
        { States::SettingProcess, "SettingProcess" },
        { States::Running, "Running" },
        { States::Aborting, "Aborting" }
    };

    auto it = stateMap.find(s);
    return (it != stateMap.end()) ? it->second : "[Unknown State_type]";
}

#endif // STATES_ENUMERATION_H