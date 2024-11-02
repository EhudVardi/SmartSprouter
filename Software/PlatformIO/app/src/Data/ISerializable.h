#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H


class ISerializable {
public:
    // Utility function to copy a member and return the next memory location
    uint8_t* serializeMember(const void* member, size_t size, uint8_t* buffer) const {
        memcpy(buffer, member, size);
        return buffer + size;  // Return next available location in the buffer
    }

    uint8_t* deserializeMember(void* member, size_t size, const uint8_t* buffer) const {
        memcpy(member, buffer, size);
        return (uint8_t*)(buffer + size);  // Return next memory location
    }

    // Base case for variadic template recursion: do nothing when no arguments
    uint8_t* serializeAll(uint8_t* buffer) const {
        return buffer;
    }

    // Variadic template function that recursively serializes each argument
    template <typename T, typename... Args>
    uint8_t* serializeAll(uint8_t* buffer, const T& member, const Args&... args) const {
        return serializeAll(serializeMember(&member, sizeof(member), buffer), args...);
    }

    // Base case for deserialization (empty argument list)
    uint8_t* deserializeAll(const uint8_t* buffer) const {
        return (uint8_t*)buffer;
    }

    // Variadic template function to deserialize each argument
    template <typename T, typename... Args>
    uint8_t* deserializeAll(const uint8_t* buffer, T& member, Args&... args) const {
        return deserializeAll(deserializeMember(&member, sizeof(member), buffer), args...);
    }

    virtual uint8_t* serialize(uint8_t* buffer) const = 0;
    virtual const uint8_t* deserialize(const uint8_t* buffer) = 0;
    virtual size_t getSerializedSize() const = 0;
};

#endif // ISERIALIZABLE_H
