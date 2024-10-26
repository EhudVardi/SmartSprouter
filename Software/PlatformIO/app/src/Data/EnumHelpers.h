#ifndef ENUM_HELPER_ENUMERATION_H
#define ENUM_HELPER_ENUMERATION_H

#include "Data/EnumHelper.h"

#include "StateMachine/App/AppStatesEnum.h"
#include "StateMachine/Setup/SetupStatesEnum.h"

namespace EnumHelpers {
    extern EnumHelper<AppStates> AppStatesHelper;
    extern EnumHelper<SetupStates> SetupStatesHelper;
}

#endif // ENUM_HELPER_ENUMERATION_H