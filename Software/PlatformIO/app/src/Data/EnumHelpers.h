#ifndef ENUM_HELPER_ENUMERATION_H
#define ENUM_HELPER_ENUMERATION_H

#include "Data/EnumHelper.h"

#include "StateMachine/App/AppStatesEnum.h"
#include "StateMachine/App/AppErrorsEnum.h"
#include "StateMachine/Setup/SetupStatesEnum.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"
#include "GUI/Pages/Pages.h"

namespace EnumHelpers {
    extern EnumHelper<AppStates> AppStatesHelper;
    extern EnumHelper<AppErrors> AppErrorsHelper;
    extern EnumHelper<SetupStates> SetupStatesHelper;
    extern EnumHelper<HumidifierActions> HumidifierActionsHelper;
    extern EnumHelper<Pages> PagesHelper;
}

#endif // ENUM_HELPER_ENUMERATION_H