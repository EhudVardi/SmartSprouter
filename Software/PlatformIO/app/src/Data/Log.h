#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include <iostream>
#include <string>

class Log {
public:
    static Log& Instance() {
        static Log instance;
        return instance;
    }

    void Write(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log() = default;
    ~Log() = default;
};

// Overload for const char*
inline void log(const char* message) {
    Log::Instance().Write(std::string(message)); // Convert const char* to std::string
}

inline void log(const std::string& message) {
    Log::Instance().Write(message);
}

inline void log(const String& message) {
    Log::Instance().Write(std::string(message.c_str())); // Convert String to std::string
}

#endif // LOG_H