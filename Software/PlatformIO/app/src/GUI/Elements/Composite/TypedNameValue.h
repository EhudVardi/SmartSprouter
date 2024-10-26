#ifndef NAMEDVALUEINT_H
#define NAMEDVALUEINT_H

#include "GUI/Elements/Composite/NamedValue.h"
#include "Data/DisplayTypes.h"

class NamedValueInt : public NamedValue<int> {
public:
    NamedValueInt(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<int>(xPos, yPos, name, size) {
        // Set a custom formatter for general int display
        valueLabel.SetFormatter([](int value) {
            return String(value);
        });
    }
    NamedValueInt(int xPos, int yPos, int initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValueInt(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEINT_H


#ifndef NAMEDVALUEFLOAT_H
#define NAMEDVALUEFLOAT_H

class NamedValueFloat : public NamedValue<float> {
public:
    NamedValueFloat(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            return String(value);
        });
    }
    NamedValueFloat(int xPos, int yPos, float initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEFLOAT_H


#ifndef NAMEDVALUEPERCENT_H
#define NAMEDVALUEPERCENT_H

class NamedValuePercent : public NamedValueFloat {
public:
    NamedValuePercent(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            char buffer[8];
            snprintf(buffer, sizeof(buffer), "%3.1f%%", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUEPERCENT_H


#ifndef NAMEDVALUETEMPERATURE_H
#define NAMEDVALUETEMPERATURE_H

class NamedValueTemperature : public NamedValueFloat {
public:
    NamedValueTemperature(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), "%3.1fC", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUETEMPERATURE_H


#ifndef NAMEDVALUEDATE_H
#define NAMEDVALUEDATE_H

class NamedValueDate : public NamedValue<DisplayDate> {
public:
    NamedValueDate(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDate>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayDate value) {
            return value.ToString();
        });
    }

    bool SetDate(int d, int m, int y) {
        DisplayDate newDate;
        if (!newDate.SetDate(d, m, y))
            return false;
        SetValue(newDate);
        return true;
    }
};

#endif // NAMEDVALUEDATE_H

#ifndef NAMEDVALUETIME_H
#define NAMEDVALUETIME_H

class NamedValueTime : public NamedValue<DisplayTime> {
public:
    NamedValueTime(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayTime>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayTime value) {
            return value.ToString();
        });
    }

    bool SetTime(int s, int m, int h) {
        DisplayTime newTime;
        if (!newTime.SetTime(s, m, h))
            return false;
        SetValue(newTime);
        return true;
    }
};

#endif // NAMEDVALUETIME_H

#ifndef NAMEDVALUEDURATION_H
#define NAMEDVALUEDURATION_H

class NamedValueDuration : public NamedValue<DisplayDuration> {
public:
    NamedValueDuration(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDuration>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayDuration value) {
            return value.ToString();
        });
    }

    void AddSeconds(int secs) { DisplayDuration newDuration = GetValue(); newDuration.AddSeconds(secs); SetValue(newDuration); }
    void AddMinutes(int mins) { DisplayDuration newDuration = GetValue(); newDuration.AddMinutes(mins); SetValue(newDuration); }
    void AddHours(int hrs) { DisplayDuration newDuration = GetValue(); newDuration.AddHours(hrs); SetValue(newDuration); }
    void AddDays(int days) { DisplayDuration newDuration = GetValue(); newDuration.AddDays(days); SetValue(newDuration); }

    void TickDown() {
        DisplayDuration newDuration = GetValue(); newDuration.TickDown(); SetValue(newDuration);
    }
};

#endif // NAMEDVALUEDURATION_H



#include "Data/EnumHelpers.h"

#ifndef NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H
#define NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H

#include "SystemContext/SystemManagers/ActuatorActions.h"

class NamedValueHumidifierActions : public NamedValue<HumidifierActions> {
public:
    NamedValueHumidifierActions(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<HumidifierActions>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](HumidifierActions value) {
            using namespace EnumHelpers;
            return String(EnumHelpers::HumidifierActionsHelper.ToString(value));
        });
    }
    NamedValueHumidifierActions(int xPos, int yPos, HumidifierActions initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValueHumidifierActions(xPos, yPos, name, size) {
        SetValue(initialValue);
    }

    void SelectNextValue() {
        using namespace EnumHelpers;
        valueLabel.SetValue(EnumHelpers::HumidifierActionsHelper.Next(valueLabel.GetValue()));
    }
};

#endif // NAMEDVALUE_ACTUATOR_HUMIDITY_ACTIONS_H