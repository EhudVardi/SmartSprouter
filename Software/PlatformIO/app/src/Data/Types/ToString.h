#ifndef TOSTRING_H
#define TOSTRING_H

/*
these are toString definitions for types that the arduino String type cannot handle.
it is (currently) used in Label type (and can be used in Range type) to provide a default formatter for generic type T, when T is of type "DisplayDate","DisplayTime" and "DisplayDuration"
when adding new custom type to be used as the Value/Range type, add a toString in the new custom type and then add a new specific template here for that type.
*/

#include <Arduino.h>

/// Generic toString implementations
// Generic type
template <typename T>
inline String toString(const T& value) {
    return String(value);
}
// my custom types
#include "AppTypes.h"
template <>
inline String toString(const AppDateTime& value) {
    return value.ToString(); // Assuming your class has a toString() member function
}
template <>
inline String toString(const AppTimeSpan& value) {
    return value.ToString(); // Assuming your class has a toString() member function
}
// my custom enumerations
#include "EnumHelpers.h"
#include "Logic/StateMachine/App/AppStatesEnum.h"
template <>
inline String toString(const AppStates& value) {
    using namespace EnumHelpers;
    return EnumHelpers::appStatesHelper.ToString(value);
}
#include "Logic/StateMachine/Setup/SetupStatesEnum.h"
template <>
inline String toString(const SetupStates& value) {
    using namespace EnumHelpers;
    return EnumHelpers::setupStatesHelper.ToString(value);
}
#include "SystemContext/SystemManagers/ActuatorActions.h"
template <>
inline String toString(const HumidifierActions& value) {
    using namespace EnumHelpers;
    return EnumHelpers::humidifierActionsHelper.ToString(value);
}
// common primitives
template <>
inline String toString(const VentilatorActions& value) {
    using namespace EnumHelpers;
    return EnumHelpers::ventilatorActionsHelper.ToString(value);
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
