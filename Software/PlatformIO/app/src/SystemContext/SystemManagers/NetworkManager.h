#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "BaseManager.h"
#include "Data/Network/NTPHandler.h"
#include "Data/Network/WifiHandler.h"

class NetworkManager : public BaseManager {
private:
    WiFiHandler wifiHandler;
    NTPHandler* ntpHandler = nullptr;

public:
    bool initialize() override;

    bool GetTimeFromNTPService(time_t& currentEpoch);

};

#endif // NETWORK_MANAGER_H
