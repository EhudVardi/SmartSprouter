#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

class ProcessManager {
public:
    void saveProcessState();  // Save long-term process state to flash
    void loadProcessState();  // Load state from flash on boot
};

#endif // PROCESS_MANAGER_H
