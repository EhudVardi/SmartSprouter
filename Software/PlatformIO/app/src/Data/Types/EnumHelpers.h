#ifndef ENUM_HELPER_ENUMERATION_H
#define ENUM_HELPER_ENUMERATION_H

#include "EnumHelper.h"
#include "Logic/StateMachine/App/AppStatesEnum.h"
#include "Logic/StateMachine/App/AppErrorsEnum.h"
#include "Logic/StateMachine/Setup/SetupStatesEnum.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"
#include "GUI/Pages/Pages.h"
#include "Data/Log/LogType.h"
#include "Logic/Process/ProcessEvents.h"

namespace EnumHelpers {
    extern EnumHelper<AppStates> appStatesHelper;
    extern EnumHelper<AppErrors> appErrorsHelper;
    extern EnumHelper<SetupStates> setupStatesHelper;
    extern EnumHelper<HumidifierActions> humidifierActionsHelper;
    extern EnumHelper<VentilatorActions> ventilatorActionsHelper;
    extern EnumHelper<Pages> pagesHelper;
    extern EnumHelper<LogType> logTypeHelper;
    extern EnumHelper<PeriodicEvents> periodicEventsHelper;
    extern EnumHelper<WindowEvents> windowEventsHelper;
}

#endif // ENUM_HELPER_ENUMERATION_H