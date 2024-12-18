#ifndef NAMEDVALUEINT_H
#define NAMEDVALUEINT_H

#include "NamedValue.h"
#include "Data/Types/AppTypes.h"

class NamedValueInt : public NamedValue<int> {
public:
    NamedValueInt(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValue<int>(xPos, yPos, name, size) {
        // Set a custom formatter for general int display
        valueLabel.SetFormatter([](int value) {
            return String(value);
        });
    }
    NamedValueInt(int xPos, int yPos, int initialValue, const String& name, FontSize size = FontSize::Small)
        : NamedValueInt(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEINT_H


#ifndef NAMEDVALUEFLOAT_H
#define NAMEDVALUEFLOAT_H

class NamedValueFloat : public NamedValue<float> {
public:
    NamedValueFloat(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {
        // Set a custom formatter for general float display
        valueLabel.SetFormatter([](float value) {
            return String(value);
        });
    }
    NamedValueFloat(int xPos, int yPos, float initialValue, const String& name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEFLOAT_H


#ifndef NAMEDVALUEPERCENT_H
#define NAMEDVALUEPERCENT_H

class NamedValuePercent : public NamedValueFloat {
public:
    NamedValuePercent(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        // Set a custom formatter for percentage display
        valueLabel.SetFormatter([](float value) {
            char buffer[11];
            snprintf(buffer, sizeof(buffer), "%3.1f%%    ", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUEPERCENT_H


#ifndef NAMEDVALUETEMPERATURE_H
#define NAMEDVALUETEMPERATURE_H

class NamedValueTemperature : public NamedValueFloat {
public:
    NamedValueTemperature(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        // Set a custom formatter for temperature display with "C" appended
        valueLabel.SetFormatter([](float value) {
            char buffer[11];
            snprintf(buffer, sizeof(buffer), "%3.1fC    ", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUETEMPERATURE_H


#ifndef NAMEDVALUEDURATION_H
#define NAMEDVALUEDURATION_H

class NamedValueTimeSpan : public NamedValue<AppTimeSpan> {
public:
    NamedValueTimeSpan(int xPos, int yPos, AppTimeSpan initialValue, const String& name, FontSize size = FontSize::Small)
        : NamedValueTimeSpan(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
    NamedValueTimeSpan(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValue<AppTimeSpan>(xPos, yPos, name, size) {
        // Set a custom formatter for a TimeSpan value
        valueLabel.SetFormatter([](AppTimeSpan value) {
            return value.ToString();
        });
    }

    void addSeconds(int secs) { AppTimeSpan newDuration = GetValue(); newDuration.addSeconds(secs); SetValue(newDuration); }
    void addMinutes(int mins) { AppTimeSpan newDuration = GetValue(); newDuration.addMinutes(mins); SetValue(newDuration); }
    void addHours(int hrs) { AppTimeSpan newDuration = GetValue(); newDuration.addHours(hrs); SetValue(newDuration); }
    void addDays(int days) { AppTimeSpan newDuration = GetValue(); newDuration.addDays(days); SetValue(newDuration); }
    void tickDown() { AppTimeSpan newDuration = GetValue(); newDuration.tickDown(); SetValue(newDuration); }
};

#endif // NAMEDVALUEDURATION_H


#include "Data/Types/EnumHelpers.h"

#ifndef NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H
#define NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H

#include "SystemContext/SystemManagers/ActuatorActions.h"

class NamedValueHumidifierActions : public NamedValue<HumidifierActions> {
public:
    NamedValueHumidifierActions(int xPos, int yPos, const String& name, FontSize size = FontSize::Small)
        : NamedValue<HumidifierActions>(xPos, yPos, name, size) {
        // Set a custom formatter for HumidifierActions enum value
        valueLabel.SetFormatter([](HumidifierActions value) {
            using namespace EnumHelpers;
            return String(EnumHelpers::humidifierActionsHelper.ToString(value));
        });
    }
    NamedValueHumidifierActions(int xPos, int yPos, HumidifierActions initialValue, const String& name, FontSize size = FontSize::Small)
        : NamedValueHumidifierActions(xPos, yPos, name, size) {
        SetValue(initialValue);
    }

    void SelectNextValue() {
        using namespace EnumHelpers;
        valueLabel.SetValue(EnumHelpers::humidifierActionsHelper.next(valueLabel.GetValue()));
    }
    void SelectPrevValue() {
        using namespace EnumHelpers;
        valueLabel.SetValue(EnumHelpers::humidifierActionsHelper.prev(valueLabel.GetValue()));
    }
};

#endif // NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H