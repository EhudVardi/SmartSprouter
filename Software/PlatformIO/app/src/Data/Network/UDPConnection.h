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
    bool isOpen = false;
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

    bool open() {
        if (!isOpen) {
            isOpen = udp.begin(port);
        }
        return isOpen;
    }

    bool sendRequest() {
        if (!isOpen) return false;
        if (bufferInitFunc) bufferInitFunc(packetBuffer);
        udp.beginPacket(targetAddress, port);
        udp.write(packetBuffer, packetSize);
        return udp.endPacket() == 1; // Return true if packet sent successfully
    }

    int receiveResponse(int timeout) {
        if (!isOpen) return -1; // Error code for not open
        udp.setTimeout(timeout);
        int packetSize = udp.parsePacket();
        return packetSize ? udp.read(packetBuffer, this->packetSize) : 0;
    }

    byte* getPacketBuffer() {
        return packetBuffer;
    }
};

#endif // UDPCONNECTION_H
