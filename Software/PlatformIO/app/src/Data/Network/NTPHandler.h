#ifndef NTP_HANDLER_H
#define NTP_HANDLER_H

#include <Arduino.h>
#include "WiFiHandler.h"

class NTPHandler {
private:
    const std::string ntpServer;
    int ntpPort;
    std::string connectionName; // Connection name in WiFiHandler

public:
    NTPHandler(const std::string& server, int port) : 
        ntpServer(server), ntpPort(port), connectionName("NTPConnection") { }

    void setupNTPConnection(WiFiHandler& wifiHandler) {
        // Create a UDP connection within WiFiHandler
        wifiHandler.createConnection(connectionName, ntpServer.c_str(), ntpPort, 48);
        // Set buffer initialization function for an NTP request
        wifiHandler.setBufferInitFunc(connectionName, [](byte* buffer) {
            memset(buffer, 0, 48); // Zero the buffer
            buffer[0] = 0b00100011; // Set the first byte for NTP request
        });
    }

    void begin(WiFiHandler& wifiHandler) {
        wifiHandler.openConnection(connectionName);
    }

    bool fetchCurrentTime(time_t& currentEpoch, WiFiHandler& wifiHandler, int attempts = 10, int attemptDelayMS = 300) {
        while (attempts--) {
            log(String(attempts) + " attempts remain to fetch ntp time");

            // Send NTP request and wait for response with 2 second timeout
            wifiHandler.sendRequest(connectionName);
            int responseSize = wifiHandler.receiveResponse(connectionName, 2000);
            // Handle response data
            if (responseSize > 0) {
                byte* responseBuffer = wifiHandler.getPacketBuffer(connectionName);
                if (!responseBuffer) 
                    continue;
                // Extract the time from the packet
                unsigned long highWord = word(responseBuffer[40], responseBuffer[41]);
                unsigned long lowWord = word(responseBuffer[42], responseBuffer[43]);
                unsigned long secsSince1900 = highWord << 16 | lowWord;
                currentEpoch = secsSince1900 - 2208988800UL; // Convert to Unix time
                return true;
            }
            delay(attemptDelayMS);
        }
        return false;
    }
};

#endif // NTP_HANDLER_H
