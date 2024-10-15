#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include "BaseManager.h"

class ActuatorManager : public BaseManager {
public:
    bool initialize() override;
    void setOutput(); 
};

#endif // ACTUATOR_MANAGER_H
