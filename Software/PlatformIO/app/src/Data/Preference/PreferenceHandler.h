#ifndef PREFERENCEMANAGER_H
#define PREFERENCEMANAGER_H

#include <Preferences.h>
#include <type_traits>
#include "Data/Serialization/ISerializable.h"

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
    const char* keySizePrefix = "_ks"; // Suffix for size keys
    const int NVS_KEY_NAME_MAX_SIZE = 16; // a definition from nvs.h, of the maximum size of any key

    bool validateKeyLength(const char* key) const;
    bool saveSizeKey(const char* key, size_t size);
    bool loadSizeKey(const char* key, size_t& size);
};

// Template implementations in the header file
template <typename T, typename>
bool PreferenceHandler::saveObjectToNVS(const T& obj, const char* key) {
    if (!validateKeyLength(key)) return false;

    size_t bufferSize = obj.getSerializedSize();
    if (strstr(key, keySizePrefix) != nullptr) return false; // Prevent using keys ending in keySizePrefix

    if (!saveSizeKey(key, bufferSize)) return false;

    uint8_t* buffer = new uint8_t[bufferSize];
    obj.serialize(buffer);

    size_t bytesWritten = preferences.putBytes(key, buffer, bufferSize);
    delete[] buffer;

    return bytesWritten == bufferSize;
}

template <typename T, typename>
bool PreferenceHandler::loadObjectFromNVS(T& obj, const char* key) {
    if (!validateKeyLength(key)) return false;

    size_t bufferSize;
    if (!loadSizeKey(key, bufferSize)) return false;

    uint8_t* buffer = new uint8_t[bufferSize];
    size_t bytesRead = preferences.getBytes(key, buffer, bufferSize);
    if (bytesRead != bufferSize) {
        delete[] buffer;
        return false;
    }
    obj.deserialize(buffer);  // Deserialize the byte array into the object
    delete[] buffer;

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
