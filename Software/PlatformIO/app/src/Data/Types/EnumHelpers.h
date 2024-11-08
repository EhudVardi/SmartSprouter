#ifndef ENUM_HELPER_ENUMERATION_H
#define ENUM_HELPER_ENUMERATION_H

#include "EnumHelper.h"
#include "StateMachine/App/AppStatesEnum.h"
#include "StateMachine/App/AppErrorsEnum.h"
#include "StateMachine/Setup/SetupStatesEnum.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"
#include "GUI/Pages/Pages.h"
#include "Data/Log/LogType.h"
#include "Logic/Process/ProcessEvents.h"

namespace EnumHelpers {
    extern EnumHelper<AppStates> AppStatesHelper;
    extern EnumHelper<AppErrors> AppErrorsHelper;
    extern EnumHelper<SetupStates> SetupStatesHelper;
    extern EnumHelper<HumidifierActions> HumidifierActionsHelper;
    extern EnumHelper<Pages> PagesHelper;
    extern EnumHelper<LogType> LogTypeHelper;
    extern EnumHelper<PeriodicEvents> PeriodicEventsHelper;
    extern EnumHelper<WindowEvents> WindowEventsHelper;
}

#endif // ENUM_HELPER_ENUMERATION_H