#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H

#include "ActionableEvent.h"

class WindowEvent : public ActionableEvent<float> {
public:
    // Default constructor
    WindowEvent() : WindowEvent(0, 100) {}
    // Constructor with thresholds only (empty callbacks)
    WindowEvent(float p_lowThreshold, float p_highThreshold) : ActionableEvent() {
        setThresholds(p_lowThreshold, p_highThreshold);
    }
    
    void setThresholds(float p_lowThreshold, float p_highThreshold) {
        lowThreshold = p_lowThreshold;
        highThreshold = p_highThreshold;
    }
    
    virtual void check(float data) override {
        if (!activeSynchronized) { // one time logic - use the data to sync active value, without comparing to previous active value
            if (data < lowThreshold) {
                startAction();
                this->active = true;
            } else if (data > highThreshold) {
                stopAction();
                this->active = false;
            } else { 
                this->active = false; 
            }
            activeSynchronized = true; // sync done
        } else {
            if (this->active == false && data < lowThreshold) {
                startAction();
                this->active = true; // Should activate
            } 
            else if (this->active == true && data > highThreshold) {
                stopAction();
                this->active = false; // Should deactivate
            } 
            //else { } // Maintain current state if within thresholds (hysteresis)
        }
    }
    
    uint8_t* serialize(uint8_t* buffer) const override {
        buffer = ActionableEvent::serialize(buffer);
        buffer = serializeMember(&lowThreshold, buffer);
        return serializeMember(&highThreshold, buffer);
    }
    const uint8_t* deserialize(const uint8_t* buffer) override {
        buffer = ActionableEvent::deserialize(buffer);
        buffer = deserializeMember(&lowThreshold, buffer);
        return deserializeMember(&highThreshold, buffer);
    }
    size_t getSerializedSize() const override {
        int size = ActionableEvent::getSerializedSize() + sizeof(lowThreshold) + sizeof(highThreshold);
        return size;
    }

    // equal operator overload
    bool operator==(const WindowEvent& other) const {
        return lowThreshold == other.lowThreshold &&
               highThreshold == other.highThreshold &&
               active == other.active;
    }
    bool operator!=(const WindowEvent& other) const {
        return !(*this == other);
    }

    String ToString() const {
        String str = "WindowEvent { ";
        str += "lowThreshold: " + String(lowThreshold) + ", ";
        str += "highThreshold: " + String(highThreshold) + ", ";
        str += ActionableEvent::ToString() + " }";
        return str;
    }

private:
    float lowThreshold;
    float highThreshold;
};

#endif // WINDOWEVENT_H
