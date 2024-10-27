#ifndef NTP_HANDLER_H
#define NTP_HANDLER_H

#include <Arduino.h>
#include <string>
#include "Data/WiFiHandler.h"
#include "Data/UDPConnection.h"

class NTPHandler {
private:
    const std::string ntpServer; // NTP server address
    std::string connectionName; // Connection name in the WiFiHandler
    UDPConnection* udpConnection; // Pointer to the UDPConnection instance

public:
    // Constructor
    NTPHandler(const std::string& server, WiFiHandler& wifiHandler)
        : ntpServer(server), connectionName("NTPConnection") {
        // Instantiate a UDPConnection instance
        udpConnection = new UDPConnection(ntpServer.c_str(), 123, 48);
        
        // Set the buffer initialization function
        udpConnection->setBufferInitFunc([](byte* buffer) {
            memset(buffer, 0, 48); // Zero the buffer
            buffer[0] = 0b00100011; // Set the first byte for NTP request
        });

        // Add the connection to the WiFiHandler's map
        wifiHandler.addConnection(connectionName, udpConnection);
    }

    // Destructor
    ~NTPHandler() {
        delete udpConnection; // Clean up the UDP connection
    }

    // Open the NTP connection
    void begin(WiFiHandler& wifiHandler) {
        wifiHandler.openConnection(connectionName);
    }

    // Fetch the current time from the NTP server
    bool fetchCurrentTime(time_t& currentEpoch, WiFiHandler& wifiHandler) {
        // Send NTP request
        wifiHandler.sendRequest(connectionName);

        // Wait for response
        int responseSize = wifiHandler.receiveResponse(connectionName, 2000); // 2-second timeout
        if (responseSize > 0) {
            byte* responseBuffer = udpConnection->getPacketBuffer();
            // Extract the time from the packet
            unsigned long highWord = word(responseBuffer[40], responseBuffer[41]);
            unsigned long lowWord = word(responseBuffer[42], responseBuffer[43]);
            unsigned long secsSince1900 = highWord << 16 | lowWord;
            currentEpoch = secsSince1900 - 2208988800UL; // Convert to Unix time
            return true; // Successfully fetched time
        }
        return false; // Failed to fetch time
    }
};

#endif // NTP_HANDLER_H
