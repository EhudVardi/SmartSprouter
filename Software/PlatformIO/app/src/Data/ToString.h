#ifndef TOSTRING_H
#define TOSTRING_H

/// these are toString definitions for types that the arduino String type cannot handle.
/// it is (currently) used in Label type (and can be used in Range type) to provide a default formatter for generic type T, when T is of type "DisplayDate","DisplayTime" and "DisplayDuration"
/// when adding new custom type to be used as the Value/Range type, add a toString in the new custom type and then add a new specific template here for that type.

#include <Arduino.h>

// Generic type
template <typename T>
inline String toString(const T& value) {
    return String(value);
}

// my custom types
#include "Data/DisplayTypes.h"
template <>
inline String toString(const DisplayDate& value) {
    return value.ToString();
}
template <>
inline String toString(const DisplayTime& value) {
    return value.ToString(); // Assuming your class has a toString() member function
}
template <>
inline String toString(const DisplayDuration& value) {
    return value.ToString(); // Assuming your class has a toString() member function
}

// common primitives
template <>
inline String toString<int>(const int& value) {
    return String(value);
}

template <>
inline String toString<float>(const float& value) {
    return String(value);
}

template <>
inline String toString<double>(const double& value) {
    return String(value);
}

#endif // TOSTRING_H
