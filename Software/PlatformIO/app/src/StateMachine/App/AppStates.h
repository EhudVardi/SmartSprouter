#include "StateMachine/App/AppState.h"
#include "SystemContext/SystemContext.h"

#ifndef ABORTING_STATE_H
#define ABORTING_STATE_H

class AbortingState : public AppState {
private:
    std::shared_ptr<PageAppAbort> abortPage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // ABORTING_STATE_H

#ifndef IDLING_STATE_H
#define IDLING_STATE_H

class IdlingState : public AppState {
private:
    std::shared_ptr<PageAppIdle> idlePage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // IDLING_STATE_H

#ifndef INFORMAING_STATE_H
#define INFORMAING_STATE_H

class InformingState : public AppState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // INFORMAING_STATE_H

#ifndef INITIALIZING_STATE_H
#define INITIALIZING_STATE_H

class InitializingState : public AppState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // INITIALIZING_STATE_H

#ifndef RUNNING_STATE_H
#define RUNNING_STATE_H

class RunningState : public AppState {
private:
    std::shared_ptr<PageAppRun> runPage = nullptr;
    
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // RUNNING_STATE_H

#ifndef SETTING_PROCESS_STATE_H
#define SETTING_PROCESS_STATE_H

#include "StateMachine/Setup/SetupStateMachine.h"

class SettingProcessState : public AppState {
private:
    std::shared_ptr<PageAppSetup> setupPage = nullptr;

    SetupStateMachine setupStateMachine;
    
public:
    SettingProcessState();
    
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // SETTING_PROCESS_STATE_H

#ifndef STARTING_UP_STATE_H
#define STARTING_UP_STATE_H

class StartingUpState : public AppState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // STARTING_UP_STATE_H

#ifndef SYSTEM_IN_ERROR_STATE_H
#define SYSTEM_IN_ERROR_STATE_H

class SystemInErrorState : public AppState {
public:
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // SYSTEM_IN_ERROR_STATE_H

#ifndef DIAG_STATE_H
#define DIAG_STATE_H

#include "StateMachine/Diag/DiagStateMachine.h"

class DiagnosingState : public AppState {
    std::shared_ptr<PageAppDiag> diagPage = nullptr;

    DiagStateMachine diagStateMachine;

public:
    DiagnosingState();
    
    void enter(SystemContext* context) override;
    void exit(SystemContext* context) override;
    void update(SystemContext* context) override;
    void handleInput(SystemContext* context, InputEvent event) override;
};

#endif // DIAG_STATE_H
