#include "SystemContext/SystemManagers/ProcessManager.h"
#include <iostream>

bool ProcessManager::initialize() {

    return true;
}

void ProcessManager::saveProcessState() {
    std::cout << "Saving process state to flash...\n";
}

void ProcessManager::loadProcessState() {
    std::cout << "Loading process state from flash...\n";
}
