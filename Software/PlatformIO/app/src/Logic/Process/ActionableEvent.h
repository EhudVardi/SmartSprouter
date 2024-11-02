#ifndef ACTIONABLEEVENT_H
#define ACTIONABLEEVENT_H

#include <functional>
#include "Data/ISerializable.h"

template<typename T>
class ActionableEvent : public ISerializable {
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

    virtual void serialize(uint8_t* buffer) const override {
        buffer = serializeMember(&active, sizeof(active), buffer);
    }
    virtual void deserialize(const uint8_t* buffer) override {
        buffer = deserializeMember(&active, sizeof(active), buffer);

    String ToString() const {
        String str = "ActionableEvent { ";
        str += "active: " + String(active ? "true" : "false") + " }";
        return str;
    }

protected:
    bool active;
    std::function<bool(T)> predicate;
    std::function<void()> startAction;
    std::function<void()> stopAction;
};

#endif // ACTIONABLEEVENT_H
