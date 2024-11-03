#include "Data/EnumHelpers.h"

namespace EnumHelpers {

    EnumHelper<AppStates> AppStatesHelper({
        { AppStates::StartingUp, "StartingUp" },
        { AppStates::SystemInError, "SystemInError" },
        { AppStates::Initializing, "Initializing" },
        { AppStates::Idling, "Idling" },
        { AppStates::Informing, "Informing" },
        { AppStates::SettingProcess, "SettingProcess" },
        { AppStates::Running, "Running" },
        { AppStates::Aborting, "Aborting" },
        { AppStates::Diagnosing, "Diagnosing" }
    }, AppStates::Diagnosing); // last valid state
    
    EnumHelper<AppErrors> AppErrorsHelper({
        { AppErrors::ErrInitInputManager, "ErrInitInputManager" },
        { AppErrors::ErrInitSensorManager, "ErrInitSensorManager" },
        { AppErrors::ErrInitDisplayManager, "ErrInitDisplayManager" },
        { AppErrors::ErrInitActuatorManager, "ErrInitActuatorManager" },
        { AppErrors::ErrInitProcessManager, "ErrInitProcessManager" },
        { AppErrors::ErrInitNetworkManager, "ErrInitNetworkManager" },
        { AppErrors::ErrInitTimeManager, "ErrInitTimeManager" },
    }, AppErrors::ErrInitTimeManager); // last valid state
    
    EnumHelper<SetupStates> SetupStatesHelper({
        { SetupStates::HumidityRangeSelect, "HumidityRangeSelect" },
        { SetupStates::HumidityRangeEditMin, "HumidityRangeEditMin" },
        { SetupStates::HumidityRangeEditMax, "HumidityRangeEditMax" },
        { SetupStates::TemperatureRangeSelect, "TemperatureRangeSelect" },
        { SetupStates::TemperatureRangeEditMin, "TemperatureRangeEditMin" },
        { SetupStates::TemperatureRangeEditMax, "TemperatureRangeEditMax" },
        { SetupStates::DurationSelect, "DurationSelect" },
        { SetupStates::DurationEdit, "DurationEdit" },
        { SetupStates::StartSelect, "StartSelect" }
    }, SetupStates::StartSelect); // last valid state
    
    EnumHelper<HumidifierActions> HumidifierActionsHelper({
        { HumidifierActions::Off, "  Off " },
        { HumidifierActions::Low, "  Low " },
        { HumidifierActions::High, "  High" },
    }, HumidifierActions::High); // last valid state
    
    EnumHelper<Pages> PagesHelper({
        { Pages::About, "About" },
        { Pages::Idle, "Idle" },
        { Pages::Setup, "Setup" },
        { Pages::Run, "Run" },
        { Pages::Abort, "Abort" },
        { Pages::Error, "Error" },
        { Pages::Diag, "Diag" },
    }, Pages::Diag); // last valid state
    
    EnumHelper<LogType> LogTypeHelper({
        { LogType::Info, "Info" },
        { LogType::Debug, "Debug" },
        { LogType::Error, "Error" },
    }, LogType::Error); // last valid state
    
    EnumHelper<PeriodicEvents> PeriodicEventsHelper({
        { PeriodicEvents::PeriodicEvent1, "PeriodicEvent1" },
        { PeriodicEvents::PeriodicEvent2, "PeriodicEvent2" },
        { PeriodicEvents::PeriodicEvent3, "PeriodicEvent3" },
    }, PeriodicEvents::PeriodicEvent3); // last valid state
    
    EnumHelper<WindowEvents> WindowEventsHelper({
        { WindowEvents::WindowEvent1, "WindowEvent1" },
        { WindowEvents::WindowEvent2, "WindowEvent2" },
        { WindowEvents::WindowEvent3, "WindowEvent3" },
    }, WindowEvents::WindowEvent3); // last valid state
}