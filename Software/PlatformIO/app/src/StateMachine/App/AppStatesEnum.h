#ifndef APP_STATES_ENUMERATION_H
#define APP_STATES_ENUMERATION_H

enum class AppStates {
    StartingUp,
    SystemInError,
    Initializing,
    Idling,
    Informing,
    SettingProcess,
    Running,
    Aborting,
    Diagnosing,
};

#endif // APP_STATES_ENUMERATION_H
