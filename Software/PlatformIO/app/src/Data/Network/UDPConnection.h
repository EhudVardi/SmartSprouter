#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <WiFiUdp.h>
#include <functional>

class UDPConnection {
private:
    WiFiUDP udp;
    const char* targetAddress;
    int port;
    byte* packetBuffer;
    int packetSize;
    bool isOpen = false; // Track if connection is already open
    std::function<void(byte*)> bufferInitFunc;

public:
    UDPConnection(const char* address, int port, int size)
        : targetAddress(address), port(port), packetSize(size) {
        packetBuffer = new byte[packetSize];
    }

    ~UDPConnection() {
        delete[] packetBuffer;
    }

    void setBufferInitFunc(std::function<void(byte*)> func) {
        bufferInitFunc = func;
    }

    // Open the UDP connection
    bool open() {
        if (!isOpen) {
            isOpen = udp.begin(port); // Only open if not already open
        }
        return isOpen;
    }

    // Send a request using the specified target address and port
    bool sendRequest() {
        if (!isOpen) return false; // Check if open
        if (bufferInitFunc) bufferInitFunc(packetBuffer);
        udp.beginPacket(targetAddress, port);
        udp.write(packetBuffer, packetSize);
        return udp.endPacket() == 1; // Return true if packet sent successfully
    }

    // Receive response with a timeout
    int receiveResponse(int timeout) {
        if (!isOpen) return -1; // Error code for not open
        udp.setTimeout(timeout);
        int packetSize = udp.parsePacket();
        return packetSize ? udp.read(packetBuffer, this->packetSize) : 0;
    }

    // Access the packet buffer (for processing after receive)
    byte* getPacketBuffer() {
        return packetBuffer;
    }
};

#endif // UDPCONNECTION_H
