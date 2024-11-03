#include "SystemContext/SystemManagers/ProcessManager.h"
#include "Data/Log.h"

bool ProcessManager::initialize() {
    lastUpdateTime = DateTime(SECONDS_FROM_1970_TO_2000);
    return true;
}

void ProcessManager::createCurrentProcess(float minHumidity, float maxHumidity, 
                              float minTemperature, float maxTemperature, 
                              DisplayTimeSpan ventsInterval, DisplayTimeSpan ventsDuration, 
                              DisplayTimeSpan totalDuration, 
                              std::shared_ptr<TimeManager> timeManager, std::shared_ptr<ActuatorManager> actuatorManager) {

    deleteCurrentProcess();
    Process* newProcess = new Process(totalDuration, timeManager->getCurrentTime());
    
    WindowEvent humidifiersEvent(minHumidity, maxHumidity);
    WindowEvent airConditionerEvent(minTemperature, maxTemperature);
    PeriodicEvent ventilatorsEvent(ventsInterval, ventsDuration);

    newProcess->addWindowEvent(WindowEvents::HumidifiersEvent, humidifiersEvent);
    newProcess->addWindowEvent(WindowEvents::AirConditionersEvent, airConditionerEvent);
    newProcess->addPeriodicEvent(PeriodicEvents::VentilatorsEvent, ventilatorsEvent);

    setProcessEventsCallbacks(newProcess, actuatorManager);

    currentProcess = newProcess;

    lastUpdateTime = timeManager->getCurrentTime();
}

DisplayTimeSpan ProcessManager::updateProcess(DisplayDateTime& now, float currHumidity, float currTemperatur) {

    currentProcess->updateWindowEvent(WindowEvents::HumidifiersEvent, currHumidity);
    currentProcess->updateWindowEvent(WindowEvents::AirConditionersEvent, currTemperatur);
    currentProcess->updatePeriodicEvent(PeriodicEvents::VentilatorsEvent, now);
    
    DisplayTimeSpan updatedRemainingTime = currentProcess->updateRemainingDuration(now - lastUpdateTime);
    return updatedRemainingTime;
}

bool ProcessManager::storeCurrentProcess() {
    return prefHandler->saveObjectToNVS(*currentProcess, currentProcessKey);
}
bool ProcessManager::loadProcessFromStorage(std::shared_ptr<ActuatorManager> actuatorManager) {
    deleteCurrentProcess(); // Clear any existing process to avoid memory leaks
    Process* loadedProcess = new Process(); // Dynamically allocate a new Process object
    if (prefHandler->loadObjectFromNVS(*loadedProcess, currentProcessKey)) {
        currentProcess = loadedProcess;  // Assign the loaded process to currentProcess
        setProcessEventsCallbacks(currentProcess, actuatorManager); // set events callbacks
        return true;
    } else {
        // Clean up if loading failed
        delete loadedProcess;
        return false;
    }
}
void ProcessManager::deleteCurrentProcess() {
    delete currentProcess;
    currentProcess = nullptr;
}
bool ProcessManager::deleteStoredProcess() {
    return prefHandler->clearObjectFromNVS(currentProcessKey);
}

bool ProcessManager::setProcessEventsCallbacks(Process* process, std::shared_ptr<ActuatorManager> actuatorManager){
    // check if process is not null. attempt to get each event from the process and set its start/stop callbacks
    if (process == nullptr)
        return false;
    
    WindowEvent* humidifiersEvent = process->getWindowEvent(WindowEvents::HumidifiersEvent);
    if (humidifiersEvent != nullptr) {
        humidifiersEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("humidifiersEvent Start\n");
                actuatorManager->SetHumidifiers(HumidifierActions::High);
            },
            [actuatorManager]() { 
                log("humidifiersEvent Stop\n");
                actuatorManager->SetHumidifiers(HumidifierActions::Off);
            }
        );
    } 
    else { log("failed to set event callbacks: humidifiersEvent not found in process", LogType::Error); }
    
    WindowEvent* airConditionerEvent = process->getWindowEvent(WindowEvents::AirConditionersEvent);
    if (airConditionerEvent != nullptr) {
        airConditionerEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("airConditionerEvent Start\n");
                //TODO: start cooler
            },
            [actuatorManager]() { 
                log("airConditionerEvent Stop\n");
                //TODO: start warmer
            }
        );
    } 
    else { log("failed to set event callbacks: airConditionerEvent not found in process", LogType::Error); }
    
    PeriodicEvent* ventilatorsEvent = process->getPeriodicEvent(PeriodicEvents::VentilatorsEvent);
    if (ventilatorsEvent != nullptr) {
        ventilatorsEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("ventilators Start\n");
                //TODO: start ventilators
            },
            [actuatorManager]() { 
                log("ventilators Stop\n");
                //TODO: start ventilators
            }
        );
    } 
    else { log("failed to set event callbacks: ventilatorsEvent not found in process", LogType::Error); }

    return true;
}