#include "SystemContext/ProcessManager.h"
#include <iostream>

void ProcessManager::saveProcessState() {
    std::cout << "Saving process state to flash...\n";
}

void ProcessManager::loadProcessState() {
    std::cout << "Loading process state from flash...\n";
}
