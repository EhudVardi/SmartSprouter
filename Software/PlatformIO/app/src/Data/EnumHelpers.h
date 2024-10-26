#ifndef ENUM_HELPER_ENUMERATION_H
#define ENUM_HELPER_ENUMERATION_H

#include "Data/EnumHelper.h"

#include "StateMachine/App/AppStatesEnum.h"
#include "StateMachine/Setup/SetupStatesEnum.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"

namespace EnumHelpers {
    extern EnumHelper<AppStates> AppStatesHelper;
    extern EnumHelper<SetupStates> SetupStatesHelper;
    extern EnumHelper<HumidifierActions> HumidifierActionsHelper;
}

#endif // ENUM_HELPER_ENUMERATION_H