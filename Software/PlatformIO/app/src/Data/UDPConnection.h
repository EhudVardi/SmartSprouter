#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <WiFiUdp.h>
#include <functional>

class UDPConnection {
private:
    WiFiUDP udp; // WiFiUDP instance for sending/receiving packets
    const char* targetAddress; // Target address (NTP server or others)
    int port; // Port number
    byte* packetBuffer; // Buffer for receiving data
    int packetSize; // Size of the packet
    std::function<void(byte*)> bufferInitFunc; // Function to initialize the buffer

public:
    // Constructor
    UDPConnection(const char* address, int port, int size)
        : targetAddress(address), port(port), packetSize(size) {
        packetBuffer = new byte[packetSize]; // Allocate the packet buffer
    }

    // Destructor
    ~UDPConnection() {
        delete[] packetBuffer; // Free the allocated buffer
    }

    // Set the buffer initialization function
    void setBufferInitFunc(std::function<void(byte*)> func) {
        bufferInitFunc = func;
    }

    // Open the UDP connection
    void open() {
        udp.begin(port); // Open UDP on the specified port
    }

    // Send a request using the specified target address and port
    void sendRequest() {
        if (bufferInitFunc) {
            bufferInitFunc(packetBuffer); // Initialize the buffer
        }
        udp.beginPacket(targetAddress, port); // Begin the packet
        udp.write(packetBuffer, packetSize); // Write the buffer to the packet
        udp.endPacket(); // End the packet
    }

    // Receive response with a timeout
    int receiveResponse(int timeout) {
        udp.setTimeout(timeout); // Set the timeout for receiving
        int packetSize = udp.parsePacket(); // Check for available packets
        if (packetSize) {
            return udp.read(packetBuffer, this->packetSize); // Read the packet into the buffer
        }
        return 0; // No packet received
    }

    // Access the packet buffer (for processing after receive)
    byte* getPacketBuffer() {
        return packetBuffer;
    }
};

#endif // UDPCONNECTION_H
