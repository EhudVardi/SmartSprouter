#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <map>
#include "UDPConnection.h"
#include "Data/Log.h"

class WiFiHandler {
private:
    std::map<std::string, UDPConnection*> connections; // Map to hold UDP connections

public:
    // Method to connect to Wi-Fi
    bool connect(const char* ssid, const char* password, int attempts = 3, int attemptDelayMS = 500) {
        WiFi.begin(ssid, password);
        log("Connecting to WiFi");
        while (WiFi.status() != WL_CONNECTED && attempts--) {
            delay(attemptDelayMS);
            log(".");
        }
        if (WiFi.status() == WL_CONNECTED) {
            log("Connected to WiFi!");
            return true;
        }
        else {
            log("Failed To Connect to Wifi");
            return false;
        }
    }

    // Method to disconnect from Wi-Fi
    void disconnect() {
        WiFi.disconnect();
        log("Disconnected from WiFi");
    }

    // Method to check if connected to Wi-Fi
    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }

    // Create and add a UDP connection
    void createConnection(const std::string& name, const char* address, int port, int size) {
        connections[name] = new UDPConnection(address, port, size);
    }

    // Set the buffer initialization function for a specific connection
    void setBufferInitFunc(const std::string& name, std::function<void(byte*)> func) {
        if (connections.find(name) != connections.end()) {
            connections[name]->setBufferInitFunc(func);
        }
    }

    // Open a UDP connection by name
    void openConnection(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            connections[name]->open();
        }
    }

    // Send a request through a named UDP connection
    bool sendRequest(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            connections[name]->sendRequest();
            return true;
        }
        return false;
    }

    // Receive a response from a named UDP connection with timeout
    int receiveResponse(const std::string& name, int timeout) {
        if (connections.find(name) != connections.end()) {
            return connections[name]->receiveResponse(timeout);
        }
        return 0;
    }

    // Access the packet buffer for a specific connection
    byte* getPacketBuffer(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            return connections[name]->getPacketBuffer();
        }
        return nullptr;
    }

    // Close and delete a UDP connection
    void closeConnection(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            delete connections[name];
            connections.erase(name);
        }
    }
};

#endif // WIFI_HANDLER_H
