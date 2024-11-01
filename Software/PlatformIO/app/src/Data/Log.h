#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include <iostream>
#include <string>
#include "LogType.h"
#include "Data/EnumHelpers.h"

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
            case LogType::Error: 
                std::cerr << EnumHelpers::LogTypeHelper.ToString(logType) << ": "  << message << std::endl;
                break;
        }
    }

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log() = default;
    ~Log() = default;
};

// Overload for const char*
inline void log(const char* message, LogType logType = LogType::Info) {
    Log::Instance().Write(std::string(message)); // Convert const char* to std::string
}

inline void log(const std::string& message, LogType logType = LogType::Info) {
    Log::Instance().Write(message);
}

inline void log(const String& message, LogType logType = LogType::Info) {
    Log::Instance().Write(std::string(message.c_str())); // Convert String to std::string
}

#endif // LOG_H