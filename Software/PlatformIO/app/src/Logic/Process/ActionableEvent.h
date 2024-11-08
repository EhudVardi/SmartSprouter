#ifndef ACTIONABLEEVENT_H
#define ACTIONABLEEVENT_H

#include <functional>
#include "Data/ISerializable.h"

template<typename T>
class ActionableEvent : public ISerializable {
public:
    ActionableEvent() : ActionableEvent([](){}, [](){})  {}
    ActionableEvent(std::function<void()> startAction, std::function<void()> stopAction) 
        : startAction(startAction), stopAction(stopAction), active(false), activeSynchronized(false) {}
        
    void setActionCallbacks(std::function<void()> p_startAction, std::function<void()> p_stopAction) {
        startAction = p_startAction;
        stopAction = p_stopAction;
    }

    virtual void check(T data) {} // check event conditions, modify the "active" value and call appropriate action 

    // Implementing serialization
    virtual uint8_t* serialize(uint8_t* buffer) const override { return buffer; }
    virtual const uint8_t* deserialize(const uint8_t* buffer) override { return buffer; }
    virtual size_t getSerializedSize() const override { return 0; }

    String ToString() const {
        String str = "ActionableEvent { ";
        str += "active: " + String(active ? "true" : "false") + " }";
        return str;
    }

protected:
    bool active;
    bool activeSynchronized;
    std::function<void()> startAction;
    std::function<void()> stopAction;
};

#endif // ACTIONABLEEVENT_H
