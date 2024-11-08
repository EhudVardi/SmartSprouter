#include "PreferenceHandler.h"

// Constructor
PreferenceHandler::PreferenceHandler(const char* namespaceName) {
    this->namespaceName = namespaceName;
    preferences.begin(namespaceName, false);  // Initialize NVS for read/write
}

// Destructor
PreferenceHandler::~PreferenceHandler() {
    preferences.end();  // Close NVS
}

// Clear a specific object from NVS
bool PreferenceHandler::clearObjectFromNVS(const char* key) {
    return preferences.remove(key);  // Remove the specific key, returns true on success
}

// Clear all keys in the current namespace
bool PreferenceHandler::clearNamespaceFromNVS() {
    preferences.clear();  // Clear all keys in the current namespace
    return true;  // preferences.clear() does not return an error code, so we assume success
}

bool PreferenceHandler::validateKeyLength(const char* key) const {
    size_t keyLen = strlen(key) + strlen(keySizePrefix);
    return keyLen <= NVS_KEY_NAME_MAX_SIZE;
}

bool PreferenceHandler::saveSizeKey(const char* key, size_t size) {
    std::string sizeKey = std::string(key) + keySizePrefix;
    return preferences.putBytes(sizeKey.c_str(), reinterpret_cast<const uint8_t*>(&size), sizeof(size)) == sizeof(size);
}

bool PreferenceHandler::loadSizeKey(const char* key, size_t& size) {
    std::string sizeKey = std::string(key) + keySizePrefix;
    return preferences.getBytes(sizeKey.c_str(), reinterpret_cast<uint8_t*>(&size), sizeof(size)) == sizeof(size);
}