#include "SystemContext/SystemManagers/ProcessManager.h"
#include "Data/Log.h"

bool ProcessManager::initialize() {

    return true;
}

void ProcessManager::saveProcessState() {
    log("Saving process state to flash...\n");
}

void ProcessManager::loadProcessState() {
    log("Loading process state from flash...\n");
}
