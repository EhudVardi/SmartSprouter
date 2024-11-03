#ifndef ACTIONABLEEVENT_H
#define ACTIONABLEEVENT_H

#include <functional>
#include "Data/ISerializable.h"

template<typename T>
class ActionableEvent : public ISerializable {
public:
    ActionableEvent(std::function<bool(T)> predicate, std::function<void()> startAction, std::function<void()> stopAction)
        : predicate(predicate), startAction(startAction), stopAction(stopAction), active(false) {}
        
    void setActionCallbacks(std::function<void()> p_startAction, std::function<void()> p_stopAction) {
        startAction = p_startAction;
        stopAction = p_stopAction;
    }

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

    // Implementing serialization
    virtual uint8_t* serialize(uint8_t* buffer) const override {
        return serializeMember(&active, buffer);
    }
    virtual const uint8_t* deserialize(const uint8_t* buffer) override {
        return deserializeMember(&active, buffer);
    }
    virtual size_t getSerializedSize() const override {
        return sizeof(active);
    }

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
