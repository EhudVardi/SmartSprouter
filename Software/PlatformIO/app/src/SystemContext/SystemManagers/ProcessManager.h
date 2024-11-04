#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "BaseManager.h"
#include "Data/PreferenceHandler.h"
#include "Logic/Process/Process.h"
#include "SystemContext/SystemManagers/ActuatorManager.h"
#include "SystemContext/SystemManagers/TimeManager.h"
#include "Data/Log.h"

class ProcessManager : public BaseManager {
private:
    Process* currentProcess = nullptr;
    DisplayDateTime lastUpdateTime;

    PreferenceHandler* prefHandler;
    const char* prefNamespaceKey = "AppProcess";
    const char* currentProcessKey = "CurrProcess";

    bool setProcessEventsCallbacks(Process* process, std::shared_ptr<ActuatorManager> actuatorManager);

public:
    ProcessManager() { prefHandler = new PreferenceHandler(prefNamespaceKey); }
    ~ProcessManager() { delete currentProcess; }

    bool initialize() override;
    void createCurrentProcess(float minHumidity, float maxHumidity, 
                              float minTemperature, float maxTemperature, 
                              DisplayTimeSpan ventsInterval, DisplayTimeSpan ventsDuration, 
                              DisplayTimeSpan totalDuration, 
                              std::shared_ptr<TimeManager> timeManager, std::shared_ptr<ActuatorManager> actuatorManager); //create process from args and set events + their callbacks
    DisplayTimeSpan updateProcess(const DisplayDateTime& now, float currHumidity, float currTemperature); // interval process update. update process events, update remaining time, and returns remaining time
    bool storeCurrentProcess(); //save Process instance in currentProcess into flash memory
    bool loadProcessFromStorage(std::shared_ptr<ActuatorManager> actuatorManager); //attempt to load stored process into currentProcess, return result status
    void deleteCurrentProcess(); //clear the local ptr from an instance
    bool deleteStoredProcess(); //clear a Process instance, stored in flash memory
};

#endif // PROCESS_MANAGER_H
