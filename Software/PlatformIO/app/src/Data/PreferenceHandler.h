#ifndef PREFERENCEMANAGER_H
#define PREFERENCEMANAGER_H

#include <Preferences.h>
#include <type_traits>
#include "Data/ISerializable.h"

// Base class for handling NVS
class PreferenceHandler {
public:
    PreferenceHandler(const char* namespaceName);
    ~PreferenceHandler();

    // General template for saving complex objects (ISerializable)
    template <typename T, typename = typename std::enable_if<std::is_base_of<ISerializable, T>::value>::type>
    bool saveObjectToNVS(const T& obj, const char* key);

    // General template for loading complex objects (ISerializable)
    template <typename T, typename = typename std::enable_if<std::is_base_of<ISerializable, T>::value>::type>
    bool loadObjectFromNVS(T& obj, const char* key);

    // Template specialization for primitives (int, float, etc.)
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    bool savePrimitiveToNVS(const T& value, const char* key);

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    bool loadPrimitiveFromNVS(T& value, const char* key);

    // Template for saving/loading arrays
    template <typename T>
    bool saveArrayToNVS(const T* arr, size_t length, const char* key);

    template <typename T>
    bool loadArrayFromNVS(T* arr, size_t length, const char* key);

    // Clear functions
    bool clearObjectFromNVS(const char* key);
    bool clearNamespaceFromNVS();

private:
    Preferences preferences;
    const char* namespaceName;
};

// Template implementations in the header file
template <typename T, typename>
bool PreferenceHandler::saveObjectToNVS(const T& obj, const char* key) {
    uint8_t buffer[sizeof(T)];
    obj.serialize(buffer);  // Serialize the object into a byte array
    size_t bytesWritten = preferences.putBytes(key, buffer, sizeof(T));  // Save the byte array to NVS
    return bytesWritten == sizeof(T);  // Return true if all bytes were written
}

template <typename T, typename>
bool PreferenceHandler::loadObjectFromNVS(T& obj, const char* key) {
    uint8_t buffer[sizeof(T)];
    size_t bytesRead = preferences.getBytes(key, buffer, sizeof(T));
    if (bytesRead != sizeof(T)) {
        return false;  // Object not found or size mismatch
    }
    obj.deserialize(buffer);  // Deserialize the byte array into the object
    return true;
}

template <typename T, typename>
bool PreferenceHandler::savePrimitiveToNVS(const T& value, const char* key) {
    size_t bytesWritten = preferences.putBytes(key, reinterpret_cast<const uint8_t*>(&value), sizeof(T));  // Save primitive as bytes
    return bytesWritten == sizeof(T);  // Return true if all bytes were written
}

template <typename T, typename>
bool PreferenceHandler::loadPrimitiveFromNVS(T& value, const char* key) {
    size_t bytesRead = preferences.getBytes(key, reinterpret_cast<uint8_t*>(&value), sizeof(T));
    return bytesRead == sizeof(T);  // Return true if all bytes were read
}

template <typename T>
bool PreferenceHandler::saveArrayToNVS(const T* arr, size_t length, const char* key) {
    size_t bytesWritten = preferences.putBytes(key, reinterpret_cast<const uint8_t*>(arr), length * sizeof(T));  // Save array as bytes
    return bytesWritten == length * sizeof(T);  // Return true if the full array was written
}

template <typename T>
bool PreferenceHandler::loadArrayFromNVS(T* arr, size_t length, const char* key) {
    size_t bytesRead = preferences.getBytes(key, reinterpret_cast<uint8_t*>(arr), length * sizeof(T));
    return bytesRead == length * sizeof(T);  // Return true if the full array was read
}

#endif
