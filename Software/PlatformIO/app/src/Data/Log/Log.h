#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "LogType.h"
#include "Data/Types/EnumHelpers.h"

class Log {
public:
    static Log& Instance() {
        static Log instance;
        return instance;
    }

    void Write(const std::string& message, LogType logType = LogType::Info) {
        switch(logType) {
            case LogType::Info: 
                std::cout << EnumHelpers::LogTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
            case LogType::Debug: 
                std::cout << EnumHelpers::LogTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
            case LogType::Error: 
                std::cerr << EnumHelpers::LogTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
        }
    }

    void PrintBufferHex(const uint8_t* buffer, size_t size, LogType logType = LogType::Info) {
        std::ostringstream oss;  // Create the output string stream
        for (size_t i = 0; i < size; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
        }
        Write(oss.str(), logType);  // Log the hexadecimal representation
    }

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log() = default;
    ~Log() = default;
};

// Overload for const char*
inline void log(const char* message, LogType logType = LogType::Info) {
    Log::Instance().Write(std::string(message), logType);
}

inline void log(const std::string& message, LogType logType = LogType::Info) {
    Log::Instance().Write(message, logType);
}

inline void log(const String& message, LogType logType = LogType::Info) {
    Log::Instance().Write(std::string(message.c_str()), logType);
}

// Log the buffer in hexadecimal format
inline void logBufferHex(const uint8_t* buffer, size_t size, LogType logType = LogType::Info) {
    Log::Instance().PrintBufferHex(buffer, size, logType);
}

#endif // LOG_H