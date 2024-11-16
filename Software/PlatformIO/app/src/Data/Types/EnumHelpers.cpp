#include "EnumHelpers.h"

namespace EnumHelpers {

    EnumHelper<AppStates> appStatesHelper({
        { AppStates::STARTING_UP, "STARTING_UP" },
        { AppStates::SYSTEM_IN_ERROR, "SYSTEM_IN_ERROR" },
        { AppStates::INITIALIZING, "INITIALIZING" },
        { AppStates::IDLING, "IDLING" },
        { AppStates::INFORMING, "INFORMING" },
        { AppStates::SETTING_PROCESS, "SETTING_PROCESS" },
        { AppStates::RUNNING, "RUNNING" },
        { AppStates::ABORTING, "ABORTING" },
        { AppStates::DIAGNOSING, "DIAGNOSING" }
    }, AppStates::DIAGNOSING); // last valid state
    
    EnumHelper<AppErrors> appErrorsHelper({
        { AppErrors::ERR_INIT_INPUT_MANAGER, "ERR_INIT_INPUT_MANAGER" },
        { AppErrors::ERR_INIT_SENSOR_MANAGER, "ERR_INIT_SENSOR_MANAGER" },
        { AppErrors::ERR_INIT_DISPLAY_MANAGER, "ERR_INIT_DISPLAY_MANAGER" },
        { AppErrors::ERR_INIT_ACTUATOR_MANAGER, "ERR_INIT_ACTUATOR_MANAGER" },
        { AppErrors::ERR_INIT_PROCESS_MANAGER, "ERR_INIT_PROCESS_MANAGER" },
        { AppErrors::ERR_INIT_NETWORK_MANAGER, "ERR_INIT_NETWORK_MANAGER" },
        { AppErrors::ERR_INIT_TIME_MANAGER, "ErrInitTimeManager" },
    }, AppErrors::ERR_INIT_TIME_MANAGER); // last valid state
    
    EnumHelper<SetupStates> setupStatesHelper({
        { SetupStates::HUMIDITY_RANGE_SELECT, "HUMIDITY_RANGE_SELECT" },
        { SetupStates::HUMIDITY_RANGE_EDIT_MIN, "HUMIDITY_RANGE_EDIT_MIN" },
        { SetupStates::HUMIDITY_RANGE_EDIT_MAX, "HUMIDITY_RANGE_EDIT_MAX" },
        { SetupStates::TEMPERATURE_RANGE_SELECT, "TEMPERATURE_RANGE_SELECT" },
        { SetupStates::TEMPERATURE_RANGE_EDIT_MIN, "TEMPERATURE_RANGE_EDIT_MIN" },
        { SetupStates::TEMPERATURE_RANGE_EDIT_MAX, "TEMPERATURE_RANGE_EDIT_MAX" },
        { SetupStates::DURATION_SELECT, "DURATION_SELECT" },
        { SetupStates::DURATION_EDIT, "DURATION_EDIT" },
        { SetupStates::START_SELECT, "START_SELECT" }
    }, SetupStates::START_SELECT); // last valid state
    
    EnumHelper<HumidifierActions> humidifierActionsHelper({
        { HumidifierActions::OFF, "  OFF " },
        { HumidifierActions::LOW, "  LOW " },
        { HumidifierActions::HIGH, "  HIGH" },
    }, HumidifierActions::HIGH); // last valid state
    
    EnumHelper<Pages> pagesHelper({
        { Pages::About, "About" },
        { Pages::Idle, "Idle" },
        { Pages::Setup, "Setup" },
        { Pages::Run, "Run" },
        { Pages::Abort, "Abort" },
        { Pages::Error, "Error" },
        { Pages::Diag, "Diag" },
    }, Pages::Diag); // last valid state
    
    EnumHelper<LogType> logTypeHelper({
        { LogType::Info, "Info" },
        { LogType::Debug, "Debug" },
        { LogType::Error, "Error" },
    }, LogType::Error); // last valid state
    
    EnumHelper<PeriodicEvents> periodicEventsHelper({
        { PeriodicEvents::VentilatorsEvent, "VentilatorsEvent" },
    }, PeriodicEvents::VentilatorsEvent); // last valid state
    
    EnumHelper<WindowEvents> windowEventsHelper({
        { WindowEvents::HumidifiersEvent, "HumidifiersEvent" },
        { WindowEvents::AirConditionersEvent, "AirConditionersEvent" },
    }, WindowEvents::AirConditionersEvent); // last valid state
}