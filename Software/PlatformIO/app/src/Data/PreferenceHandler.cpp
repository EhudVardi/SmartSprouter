#include "Data/PreferenceHandler.h"

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
