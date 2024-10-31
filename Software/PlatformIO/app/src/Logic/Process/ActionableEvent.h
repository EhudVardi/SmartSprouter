#ifndef ACTIONABLEEVENT_H
#define ACTIONABLEEVENT_H

#include <functional>

template<typename T>
class ActionableEvent {
public:
    ActionableEvent(std::function<bool(T)> predicate, std::function<void()> startAction, std::function<void()> stopAction)
        : predicate(predicate), startAction(startAction), stopAction(stopAction), active(false) {}

    void check(T data) {
        if (predicate(data)) {
            if (!active) {
                startAction();
                active = true;
            }
        } else {
            if (active) {
                stopAction();
                active = false;
            }
        }
    }

protected:
    bool active;
    std::function<bool(T)> predicate;
    std::function<void()> startAction;
    std::function<void()> stopAction;
};

#endif // ACTIONABLEEVENT_H
