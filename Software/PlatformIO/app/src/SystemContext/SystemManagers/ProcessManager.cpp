#include "ProcessManager.h"
#include "Data/Log/Log.h"

bool ProcessManager::initialize() {
    lastUpdateTime = DateTime(SECONDS_FROM_1970_TO_2000);
    return true;
}

void ProcessManager::createCurrentProcess(float minHumidity, float maxHumidity, 
                              float minTemperature, float maxTemperature, 
                              AppTimeSpan ventsInterval, AppTimeSpan ventsDuration, 
                              AppTimeSpan totalDuration, 
                              const AppDateTime& now, std::shared_ptr<ActuatorManager> actuatorManager) {

    deleteCurrentProcess();
    Process* newProcess = new Process(totalDuration, now);
    
    WindowEvent humidifiersEvent(minHumidity, maxHumidity);
    WindowEvent airConditionerEvent(minTemperature, maxTemperature);
    PeriodicEvent ventilatorsEvent(ventsInterval, ventsDuration);

    newProcess->addWindowEvent(WindowEvents::HUMIDIFIERS_EVENT, humidifiersEvent);
    newProcess->addWindowEvent(WindowEvents::AIR_CONDITIONERS_EVENT, airConditionerEvent);
    newProcess->addPeriodicEvent(PeriodicEvents::VENTILATORS_EVENT, ventilatorsEvent);

    setProcessEventsCallbacks(newProcess, actuatorManager);

    currentProcess = newProcess;

    lastUpdateTime = now;
}

AppTimeSpan ProcessManager::updateProcess(const AppDateTime& now, float currHumidity, float currTemperature) {
    
    if (!isnan(currHumidity)) currentProcess->updateWindowEvent(WindowEvents::HUMIDIFIERS_EVENT, currHumidity);
    if (!isnan(currTemperature)) currentProcess->updateWindowEvent(WindowEvents::AIR_CONDITIONERS_EVENT, currTemperature);
    currentProcess->updatePeriodicEvent(PeriodicEvents::VENTILATORS_EVENT, now);
    
    AppTimeSpan updatedRemainingTime = currentProcess->updateRemainingDuration(now - lastUpdateTime);
    lastUpdateTime = now;
    return updatedRemainingTime;
}

bool ProcessManager::storeCurrentProcess() {
    return prefHandler->saveObjectToNVS(*currentProcess, currentProcessKey);
}
bool ProcessManager::loadProcessFromStorage(const AppDateTime& now, std::shared_ptr<ActuatorManager> actuatorManager) {
    deleteCurrentProcess(); // Clear any existing process to avoid memory leaks
    Process* loadedProcess = new Process(); // Dynamically allocate a new Process object
    if (prefHandler->loadObjectFromNVS(*loadedProcess, currentProcessKey)) {
        setProcessEventsCallbacks(loadedProcess, actuatorManager); // set events callbacks
        currentProcess = loadedProcess;  // Assign the loaded process to currentProcess
        lastUpdateTime = now; // set last update to now since we just loaded the process
        return true;
    } else {
        // Clean up if loading failed
        delete loadedProcess;
        currentProcess = nullptr;
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
    
    WindowEvent* humidifiersEvent = process->getWindowEvent(WindowEvents::HUMIDIFIERS_EVENT);
    if (humidifiersEvent != nullptr) {
        humidifiersEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("humidifiersEvent Start");
                actuatorManager->SetHumidifiers(HumidifierActions::H_HIGH);
            },
            [actuatorManager]() { 
                log("humidifiersEvent Stop");
                actuatorManager->SetHumidifiers(HumidifierActions::H_OFF);
            }
        );
    } 
    else { log("failed to set event callbacks: humidifiersEvent not found in process", LogType::ERROR); }
    
    WindowEvent* airConditionerEvent = process->getWindowEvent(WindowEvents::AIR_CONDITIONERS_EVENT);
    if (airConditionerEvent != nullptr) {
        airConditionerEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("airConditionerEvent Start");
                //TODO: start cooler
            },
            [actuatorManager]() { 
                log("airConditionerEvent Stop");
                //TODO: start warmer
            }
        );
    } 
    else { log("failed to set event callbacks: airConditionerEvent not found in process", LogType::ERROR); }
    
    PeriodicEvent* ventilatorsEvent = process->getPeriodicEvent(PeriodicEvents::VENTILATORS_EVENT);
    if (ventilatorsEvent != nullptr) {
        ventilatorsEvent->setActionCallbacks(
            [actuatorManager]() { 
                log("ventilators Start");
                //TODO: start ventilators
            },
            [actuatorManager]() { 
                log("ventilators Stop");
                //TODO: start ventilators
            }
        );
    } 
    else { log("failed to set event callbacks: ventilatorsEvent not found in process", LogType::ERROR); }

    return true;
}