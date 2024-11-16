#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <map>
#include "UDPConnection.h"
#include "Data/Log/Log.h"

class WiFiHandler {
private:
    std::map<std::string, UDPConnection*> connections; // UDP connections map

public:

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

    void disconnect() {
        WiFi.disconnect();
        log("Disconnected from WiFi");
    }

    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }

    void createConnection(const std::string& name, const char* address, int port, int size) {
        connections[name] = new UDPConnection(address, port, size);
    }

    void setBufferInitFunc(const std::string& name, std::function<void(byte*)> func) {
        if (connections.find(name) != connections.end()) {
            connections[name]->setBufferInitFunc(func);
        }
    }

    void openConnection(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            connections[name]->open();
        }
    }

    bool sendRequest(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            connections[name]->sendRequest();
            return true;
        }
        return false;
    }

    int receiveResponse(const std::string& name, int timeout) {
        if (connections.find(name) != connections.end()) {
            return connections[name]->receiveResponse(timeout);
        }
        return 0;
    }

    byte* getPacketBuffer(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            return connections[name]->getPacketBuffer();
        }
        return nullptr;
    }

    void closeConnection(const std::string& name) {
        if (connections.find(name) != connections.end()) {
            delete connections[name];
            connections.erase(name);
        }
    }
};

#endif // WIFI_HANDLER_H
