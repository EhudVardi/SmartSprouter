#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "BaseManager.h"

class ProcessManager : public BaseManager {
public:
    bool initialize() override;
    void saveProcessState();  // Save long-term process state to flash
    void loadProcessState();  // Load state from flash on boot
};

#endif // PROCESS_MANAGER_H
