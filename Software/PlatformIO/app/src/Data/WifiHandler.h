#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <map>
#include "Data/UDPConnection.h"

class WiFiHandler {
private:
    std::map<std::string, UDPConnection*> connections; // Map to hold UDP connections

public:
    // Method to connect to Wi-Fi
    bool connect(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);

        Serial.print("Connecting to WiFi");
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print("."); // Display dots while connecting
        }
        Serial.println("Connected to WiFi!");
        return true; // Successfully connected
    }

    // Method to disconnect from Wi-Fi
    void disconnect() {
        WiFi.disconnect();
        Serial.println("Disconnected from WiFi");
    }

    // Method to check if connected to Wi-Fi
    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }

    // Add a UDP connection to the map
    void addConnection(const std::string& name, UDPConnection* connection) {
        connections[name] = connection;
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
};

#endif // WIFI_HANDLER_H
