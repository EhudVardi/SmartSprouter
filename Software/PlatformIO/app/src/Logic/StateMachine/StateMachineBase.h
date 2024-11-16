// StateMachineBase.h
#ifndef STATE_MACHINE_BASE_H
#define STATE_MACHINE_BASE_H

#include <memory>
#include <unordered_map>
#include "SystemContext/SystemContext.h"
#include "StateBase.h"
#include "Data/Log/Log.h"

template<typename TState, typename TEnum>
class StateMachineBase {
protected:
    std::shared_ptr<TState> currentState;
    std::unordered_map<TEnum, std::shared_ptr<TState>> stateMap;

public:
    StateMachineBase() = default;

    void addState(TEnum stateEnum, std::shared_ptr<TState> state) {
        state->setStateMachine(static_cast<typename TState::TStateMachineType*>(this)); // Static cast to the derived state machine type
        stateMap[stateEnum] = state;
    }

    void changeState(TEnum stateEnum, SystemContext* context) {
        auto newState = stateMap.find(stateEnum);
        if (newState != stateMap.end()) {
            if (currentState) {
                currentState->exit(context);
            }
            currentState = newState->second;
            if (currentState) {
                currentState->enter(context);
            }
        } else {
            log("State not found!", LogType::ERROR);
        }
    }

    void update(SystemContext* context) {
        if (currentState) {
            currentState->update(context);
        }
    }

    void handleInput(InputEvent event, SystemContext* context) {
        if (currentState) {
            currentState->handleInput(context, event);
        }
    }
};

#endif // STATE_MACHINE_BASE_H
