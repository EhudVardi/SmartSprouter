#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "BaseManager.h"
#include "Data/NTPHandler.h"
#include "Data/WifiHandler.h"

class NetworkManager : public BaseManager {
private:
    WiFiHandler wifiHandler;
    NTPHandler* ntpHandler = nullptr;

    const char* ssid = "SSID";
    const char* password = "PASSWORD";

    const char* ntpServerUrl = "pool.ntp.org";
    const int ntpPort = 123;

public:
    bool initialize() override;

    bool GetTimeFromNTPService(time_t& currentEpoch);

};

#endif // NETWORK_MANAGER_H
