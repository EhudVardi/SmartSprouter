#include "NetworkManager.h"

bool NetworkManager::initialize() {

    // init NTP handler and use WifiHandler instance to create and register a connection
    ntpHandler = new NTPHandler(ntpServerUrl, ntpPort);
    ntpHandler->setupNTPConnection(wifiHandler);
    return true;
}

bool NetworkManager::GetTimeFromNTPService(time_t& currentEpoch) {
    
    // connect to wifi network and attempt an NTP request
    bool status = false;
    if (wifiHandler.connect(ssid, password)) {
        ntpHandler->begin(wifiHandler);
        if (ntpHandler->fetchCurrentTime(currentEpoch, wifiHandler)) {
            status = true;
        }
    }
    wifiHandler.disconnect();
    return status;
}