#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <cstring>  // for memcpy
#include "Data/DisplayTypes.h"  // For DisplayDateTime and DisplayTimeSpan
#include "Logic/Process/ProcessEvents.h"

class ISerializable {
public:

    // Utility functions to copy a member and return the next memory location (raw memory serialization)
    uint8_t* serializeMember(const void* member, size_t size, uint8_t* buffer) const {
        std::memcpy(buffer, member, size);
        return buffer + size;
    }
    uint8_t* deserializeMember(void* member, size_t size, const uint8_t* buffer) const {
        std::memcpy(member, buffer, size);
        return const_cast<uint8_t*>(buffer + size);
    }

    // General template function for any type T
    template <typename T>
    uint8_t* serializeMember(const T* member, uint8_t* buffer) const {
        std::memcpy(buffer, member, sizeof(T));
        return buffer + sizeof(T);
    }
    template <typename T>
    const uint8_t* deserializeMember(T* member, const uint8_t* buffer) const {
        std::memcpy(member, buffer, sizeof(T));
        return buffer + sizeof(T);
    }

    // Specialized serialize and deserialize for float
    uint8_t* serializeMember(const float* member, uint8_t* buffer) const {
        return serializeMember(static_cast<const void*>(member), sizeof(float), buffer);
    }
    const uint8_t* deserializeMember(float* member, const uint8_t* buffer) const {
        return deserializeMember(static_cast<void*>(member), sizeof(float), buffer);
    }
    // Specialized serialize and deserialize for AppDateTime
    uint8_t* serializeMember(const AppDateTime* member, uint8_t* buffer) const {
        return serializeMember(static_cast<const void*>(member), sizeof(AppDateTime), buffer);
    }
    const uint8_t* deserializeMember(AppDateTime* member, const uint8_t* buffer) const {
        return deserializeMember(static_cast<void*>(member), sizeof(AppDateTime), buffer);
    }
    // Specialized serialize and deserialize for AppTimeSpan
    uint8_t* serializeMember(const AppTimeSpan* member, uint8_t* buffer) const {
        return serializeMember(static_cast<const void*>(member), sizeof(AppTimeSpan), buffer);
    }
    const uint8_t* deserializeMember(AppTimeSpan* member, const uint8_t* buffer) const {
        return deserializeMember(static_cast<void*>(member), sizeof(AppTimeSpan), buffer);
    }
    // Specialized serialize and deserialize for size_t
    uint8_t* serializeMember(const size_t* member, uint8_t* buffer) const {
        return serializeMember(static_cast<const void*>(member), sizeof(size_t), buffer);
    }
    const uint8_t* deserializeMember(size_t* member, const uint8_t* buffer) const {
        return deserializeMember(static_cast<void*>(member), sizeof(size_t), buffer);
    }
    // Specialized serialize and deserialize for bool
    uint8_t* serializeMember(const bool* member, uint8_t* buffer) const {
        *buffer = *member ? 1 : 0;
        return buffer + 1;
    }
    const uint8_t* deserializeMember(bool* member, const uint8_t* buffer) const {
        *member = (*buffer != 0);
        return buffer + 1;
    }
    // Specialized serialize and deserialize for PeriodicEvents
    uint8_t* serializeMember(const PeriodicEvents* member, uint8_t* buffer) const {
        *buffer++ = static_cast<uint8_t>(*member); // Serialize as uint8_t
        return buffer;
    }
    const uint8_t* deserializeMember(PeriodicEvents* member, const uint8_t* buffer) const {
        *member = static_cast<PeriodicEvents>(*buffer++); // Deserialize as uint8_t
        return buffer;
    }
    // Specialized serialize and deserialize for WindowEvents
    uint8_t* serializeMember(const WindowEvents* member, uint8_t* buffer) const {
        *buffer++ = static_cast<uint8_t>(*member); // Serialize as uint8_t
        return buffer;
    }
    const uint8_t* deserializeMember(WindowEvents* member, const uint8_t* buffer) const {
        *member = static_cast<WindowEvents>(*buffer++); // Deserialize as uint8_t
        return buffer;
    }

    // Variadic template functions for serializing and deserializing multiple members
    template <typename T, typename... Args>
    uint8_t* serializeAll(uint8_t* buffer, const T& member, const Args&... args) const {
        return serializeAll(serializeMember(&member, buffer), args...);
    }
    uint8_t* serializeAll(uint8_t* buffer) const {
        return buffer;
    }
    template <typename T, typename... Args>
    const uint8_t* deserializeAll(const uint8_t* buffer, T& member, Args&... args) const {
        return deserializeAll(deserializeMember(&member, buffer), args...);
    }
    const uint8_t* deserializeAll(const uint8_t* buffer) const {
        return buffer;
    }

    // Pure virtual functions to be implemented by subclasses
    virtual uint8_t* serialize(uint8_t* buffer) const = 0;
    virtual const uint8_t* deserialize(const uint8_t* buffer) = 0;
    virtual size_t getSerializedSize() const = 0;
};

#endif // ISERIALIZABLE_H
